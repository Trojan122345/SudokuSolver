//
// Created by Troja on 20/04/2024.
//
#include <map>
#include <string>

#ifndef SUDOKUSOLVER_ENUMS_H
#define SUDOKUSOLVER_ENUMS_H

enum FontType{
    ARIAL,
    SEGOEUIEMOJI
};

static std::map<FontType, std::string> getFontPath = {
        {ARIAL, "../res/fonts/Arial/arial.ttf"},
        {SEGOEUIEMOJI, "../res/fonts/SegoeUI/seguiemj.ttf"}
};

#endif //SUDOKUSOLVER_ENUMS_H
