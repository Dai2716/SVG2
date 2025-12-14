#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Types.h"
#include "earcut.hpp"
using namespace std;
using namespace sf;
class shape { // lop co ban cho tat ca hinh
public:
    virtual ~shape() = default; // destructor ao
    virtual void draw(RenderWindow& window) = 0; // ham ve thuong ao
    Color fill_color = Color::Black; // mau nen
    Color stroke_color = Color::Black; // mau vien
    float fill_opacity = 1.0f; // do trong suot nen
    float stroke_opacity = 1.0f; // do trong suot vien
    float stroke_width = 0.0f; // do day vien
    multi_transform trans; // bien transform
    // sf::Transform parentTransform; // transform từ group cha
};

class line : public shape { // doan thang
public:
    Vector2f start, end; // diem dau va diem cuoi
    void draw(RenderWindow& window) override; // ve line
};

class rectangle : public shape { // hinh chu nhat
public:
    Vector2f start; // goc tren trai
    float width = 0, height = 0; // chieu rong va chieu cao
    void draw(RenderWindow& window) override; // ve rectangle
};

class circle : public shape { // hinh tron
public:
    Vector2f center; // tam
    float r = 0; // ban kinh
    void draw(RenderWindow& window) override; // ve circle
};

class ellipse : public shape { // hinh elip
public:
    Vector2f start; // diem bat dau
    float rx = 0, ry = 0; // ban truc x va y
    void draw(RenderWindow& window) override; // ve ellipse
};

class polygon : public shape { // da giac
public:
    vector<Vector2f> p; // cac diem
    void draw(RenderWindow& window) override; // ve polygon
};

class polyline : public shape { // duong gap khuc
public:
    vector<Vector2f> p; // cac diem
    bool closed = false; // co dong thanh da giac khong
    void draw(RenderWindow& window) override; // ve polyline
    enum class LineCap { Butt, Round, Square };
    enum class LineJoin { Miter, Round, Bevel };
    
    LineCap stroke_linecap = LineCap::Round;
    LineJoin stroke_linejoin = LineJoin::Round;
    float stroke_miterlimit = 4.0f;
};

class text : public shape { 
public:
    Vector2f start;

    float dx = 0, dy = 0;

    float font_size = 12;
    string font_family;
    string font_style;        // italic, normal
    string font_weight;       // bold, lighter...
    string text_decoration;   // underline, overline
    string text_anchor;       // start, middle, end
    float letter_spacing = 0; 
    float word_spacing = 0;

    string dominant_baseline; // middle, hanging, text-before-edge
    string writing_mode;      // lr, tb, rl

    string text_;             // nội dung văn bản

    void draw(RenderWindow& window) override;
};


// class path : public shape {
// public:
//     string d; // path data

//     // Thuộc tính SVG
//     multi_transform trans;
//     bool has_fill = false;
//     bool has_stroke = false;
//     sf::Color fill_color = sf::Color::Transparent;
//     sf::Color stroke_color = sf::Color::Transparent;
//     float stroke_width = 1.0f;
//     float fill_opacity = 1.0f;
//     float stroke_opacity = 1.0f;

//     struct PathCommand {
//         char type;
//         vector<float> values;
//     };

//     vector<PathCommand> parsePathData() const; // parse d thành commands
//     void renderPath(sf::RenderWindow &window, const vector<PathCommand> &commands) const;

//     sf::Color getFillColor() const {
//         return sf::Color(fill_color.r, fill_color.g, fill_color.b,
//                          static_cast<uint8_t>(fill_opacity * 255));
//     }
//     sf::Color getStrokeColor() const {
//         return sf::Color(stroke_color.r, stroke_color.g, stroke_color.b,
//                          static_cast<uint8_t>(stroke_opacity * 255));
//     }

//     void draw(sf::RenderWindow &window) override ;
// };

class path : public shape {
public:
    string d; // path data

    // SVG attributes
    multi_transform trans;
    bool has_fill = false;
    bool has_stroke = false;
    sf::Color fill_color = sf::Color::Transparent;
    sf::Color stroke_color = sf::Color::Transparent;
    float stroke_width = 1.0f;
    float fill_opacity = 1.0f;
    float stroke_opacity = 1.0f;

    struct PathCommand {
        char type;
        vector<float> values;
    };

    vector<PathCommand> parsePathData() const;
    
    // NEW: triangulated vertices
    sf::VertexArray filledVertices;
    bool filledVerticesReady = false;

    void prepareFill();  // triangulate once
    void renderPath(sf::RenderWindow &window, const vector<PathCommand> &commands) const;

    sf::Color getFillColor() const {
        return sf::Color(fill_color.r, fill_color.g, fill_color.b,
                         static_cast<uint8_t>(fill_opacity * 255));
    }
    sf::Color getStrokeColor() const {
        return sf::Color(stroke_color.r, stroke_color.g, stroke_color.b,
                         static_cast<uint8_t>(stroke_opacity * 255));
    }

    void draw(sf::RenderWindow &window) override;
};
