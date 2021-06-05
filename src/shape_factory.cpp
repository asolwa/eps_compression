#include "shape_factory.h"

std::vector<ShapePtr> ShapeFactory::create(EpsDatas epsData) {
    for (auto &i:epsData) {
        if (i->getDataType() == EpsDataType::header) {
            convertHeader(i);
        } else if (i->getDataType() == EpsDataType::alias) {
            convertAlias(i);
        } else if (i->getDataType() == EpsDataType::instruction) {
            convertInstruction(i);
        }
    }
    return shapes_;
}

void ShapeFactory::convertAlias(EpsDataPtr &dataPtr) {
    std::vector<std::string> tokens = dataPtr->getTokenValues();
    std::vector<std::string> values;
    int firstNonValueIndex;
    std::string key = tokens[0];
    key.erase(key.begin(), key.begin() + 1);
    if (tokens[tokens.size() - 2] == "bind")
        firstNonValueIndex = 3;
    else
        firstNonValueIndex = 2;
    values.insert(values.begin(), tokens.begin() + 2, tokens.end() - firstNonValueIndex);
    std::pair<std::string, std::vector<std::string>> newAlias{key, values};
    declaredAliases_.insert(newAlias);
}

void ShapeFactory::convertHeader(EpsDataPtr &dataPtr) {

}

void ShapeFactory::convertInstruction(EpsDataPtr &dataPtr) {
    std::stack<std::string> instructionStack;
    std::vector<std::string> instructionVector = dataPtr->getTokenValues();
    std::string currentInstruction;

    size_t s = 0;
    while (s < instructionVector.size() || !pendingInstructions_.empty()) {
        if (!pendingInstructions_.empty()) {
            currentInstruction = pendingInstructions_.top();
            pendingInstructions_.pop();
        } else {
            currentInstruction = instructionVector[s];
            s++;
        }
        if (!replaceAlias(currentInstruction, pendingInstructions_)) {
            if (currentInstruction == "moveto" && instructionStack.size() >= 2) {
                float y = stof(instructionStack.top());
                instructionStack.pop();
                float x = stof(instructionStack.top());
                instructionStack.pop();
                currentPoint_.first = x;
                currentPoint_.second = y;
                graphics_.changeCurrentPoint(currentPoint_);
            } else if (currentInstruction == "rmoveto" && instructionStack.size() >= 2) {
                float y = stof(instructionStack.top());
                instructionStack.pop();
                float x = stof(instructionStack.top());
                instructionStack.pop();
                currentPoint_.first += x;
                currentPoint_.second += y;
                graphics_.changeCurrentPoint(currentPoint_);
            } else if (currentInstruction == "rlineto" && instructionStack.size() >= 2) {
                float y = stof(instructionStack.top());
                instructionStack.pop();
                float x = stof(instructionStack.top());
                instructionStack.pop();
                currentPoint_.first += x;
                currentPoint_.second += y;
                graphics_.addToPath(currentPoint_);
            } else if (currentInstruction == "lineto" && instructionStack.size() >= 2) {
                float y = stof(instructionStack.top());
                instructionStack.pop();
                float x = stof(instructionStack.top());
                instructionStack.pop();
                currentPoint_.first = x;
                currentPoint_.second = y;
                graphics_.addToPath(currentPoint_);
            } else if (currentInstruction == "newpath") {
                graphics_.clearPath();
            } else if (currentInstruction == "closepath") {
                graphics_.closePath();
            } else if (currentInstruction == "mul" && instructionStack.size() >= 2) {
                float y = stof(instructionStack.top());
                instructionStack.pop();
                float x = stof(instructionStack.top());
                instructionStack.pop();
                instructionStack.push(std::to_string(x * y));
            } else if (currentInstruction == "exch" && instructionStack.size() >= 2) {
                std::string x = instructionStack.top();
                instructionStack.pop();
                std::string y = instructionStack.top();
                instructionStack.pop();
                instructionStack.push(x);
                instructionStack.push(y);
            } else if (currentInstruction == "roll") {
                int j = stoi(instructionStack.top());
                instructionStack.pop();
                int n = stoi(instructionStack.top());
                instructionStack.pop();
                j = abs(j % n);
                if (n != 0 && j != 0 && instructionStack.size() >= n) {
                    std::vector<std::string> v(n);
                    for (int i = 0; i < n; i++) {
                        v[i] = instructionStack.top();
                        instructionStack.pop();
                    }
                    for (int i = 0; i < n; i++) {
                        instructionStack.push(v[(n - j + i) % n]);
                    }
                }
            } else if (currentInstruction == "copy") {
                int n = stoi(instructionStack.top());
                instructionStack.pop();
                std::string copiedElement = instructionStack.top();
                for (int i = 0; i < n; i++)
                    instructionStack.push(copiedElement);
            } else if (currentInstruction == "showpage") {

            } else if (currentInstruction == "grestore") {
                graphics_ = graphicsStack_.top();
                graphicsStack_.pop();
            } else if (currentInstruction == "gsave") {
                graphicsStack_.push(graphics_);
            } else if (currentInstruction == "fill") {
                for (auto& subPath:graphics_.getPath()) {
                    ShapePtr shape(new Shape(subPath, FillType::fill));
                    shapes_.push_back(shape);
                }
                graphics_.clearPath();
            } else if (currentInstruction == "stroke") {
                for (auto& subPath:graphics_.getPath()) {
                    ShapePtr shape(new Shape(subPath, FillType::none));
                    shapes_.push_back(shape);
                }
                graphics_.clearPath();
            } else
                instructionStack.push(currentInstruction);
        }
    }
}

bool ShapeFactory::replaceAlias(std::string &name, std::stack<std::string> &pendingInstructions) {
    auto it = declaredAliases_.find(name);
    if (it != declaredAliases_.end()) {
        for (auto i = it->second.rbegin(); i != it->second.rend(); i++) {
            pendingInstructions.push(*i);
        }
        return true;
    } else return false;
}
