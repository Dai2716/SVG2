#pragma once
#include <vector>
#include <string>
#include <map>
#include "rapidxml.hpp"
#include "Shape.h"
#include "Types.h"

// class SVGParse luu tru cac du lieu phan tich duoc tu file svg
class SVGParse
{
public:
    string filename;
    pair<unsigned int, unsigned int> frame; // kthuoc cua so
    viewBox vb;
    vector<shape *> shapes;

    SVGParse(const string &);
    ~SVGParse();

    void loadSVG(); // doc file
    void clear();
};

// struct group dung de duyet qua cau truc phan cap cua file svg
struct group
{
    map<string, string> attributes;
    void traversal_group(rapidxml::xml_node<> *root, vector<shape *> &shapes); // duyet cac group va them hinh vao vector
};