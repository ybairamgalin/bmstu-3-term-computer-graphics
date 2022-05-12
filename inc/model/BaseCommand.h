//
// Created by Yaroslav Bairamgalin on 05.05.2022.
//

#ifndef BASECOMMAND_H
#define BASECOMMAND_H

class BaseCommand
{
public:
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;
    virtual void undo() const = 0;
protected:

};

#endif //LAB_01_BASECOMMAND_H
