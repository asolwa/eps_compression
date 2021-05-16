#include <iostream>
#include "converter.h"

Converter::Converter(): currentPoint(std::make_pair<float, float>(0.0, 0.0)){};

void Converter::convert(EpsDatas epsData) {
    for (auto& i:epsData){
        if(i->getDataType() == EpsDataType::header){
            convertHeader(i);
        }
        else if(i->getDataType() == EpsDataType::alias){
            convertAlias(i);
        }
        else if(i->getDataType() == EpsDataType::instruction){
            convertInstruction(i);
        }
    }
}

void Converter::convertAlias(EpsDataPtr dataPtr)  {
    std::pair<std::string, std::string> newAlias{dataPtr->getValues()[0],dataPtr->getValues()[1]};
    declaredAliases.insert(newAlias);
}

void Converter::convertHeader(EpsDataPtr dataPtr) {

}
void Converter::convertCommand(EpsDataPtr dataPtr){
    std::string commandName = dataPtr->getValues()[0];
    checkAlias(commandName);
}

void Converter::convertInstruction(EpsDataPtr dataPtr) {
    std::stack<std::string> instructionStack;
    std::vector<std::string> instructionVector= dataPtr->getValues();
    std::string currentInstruction;

    size_t  i =  0;
    while (i < instructionVector.size()){
        currentInstruction = instructionVector[i];
        checkAlias(currentInstruction);

        if (currentInstruction == "moveto"){
            float y = stof(instructionStack.top());
            instructionStack.pop();
            float x = stof(instructionStack.top());
            instructionStack.pop();
            currentPoint.first = x;
            currentPoint.second = y;
            startingPoints.push(currentPoint);
            currentLine.push_back(currentPoint);
        }
        else if (currentInstruction == "rmoveto"){
            float y = stof(instructionStack.top());
            instructionStack.pop();
            float x = stof(instructionStack.top());
            instructionStack.pop();
            currentPoint.first += x;
            currentPoint.second += y;
        }
        else if (currentInstruction == "rlineto"){
            float y = stof(instructionStack.top());
            instructionStack.pop();
            float x = stof(instructionStack.top());
            instructionStack.pop();
            currentPoint.first += x;
            currentPoint.second += y;
            currentLine.push_back(currentPoint);
        }
        else if (currentInstruction == "lineto"){
            float y = stof(instructionStack.top());
            instructionStack.pop();
            float x = stof(instructionStack.top());
            instructionStack.pop();
            currentPoint.first = x;
            currentPoint.second = y;
            currentLine.push_back(currentPoint);
        }
        else if(currentInstruction == "closepath"){
            if(!startingPoints.empty()){
                currentLine.push_back(startingPoints.top());
                startingPoints.pop();
            }
        }
        else if(currentInstruction == "stroke"){
            convertedLines.push_back(currentLine);
            currentLine.clear();
        }
        else
            instructionStack.push(currentInstruction);
        i++;
    }
}

void Converter::checkAlias(std::string &name) {
    std::map<std::string, std::string>::iterator it = declaredAliases.find(name);
    if (it != declaredAliases.end())
        name = it->second;
}

void Converter::print() {
    for(auto& line:convertedLines){
        std::cout<< "Nowa linia\n";
        for(auto&i : line){
            std::cout<< i.first << " "<< i.second<< "\n";
        }
        std::cout<< "Koniec linii\n";
    }
}
