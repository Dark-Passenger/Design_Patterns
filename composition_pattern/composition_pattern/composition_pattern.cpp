// composition_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>

//interface class.
class BitMap
{
public:
  virtual void Add(std::unique_ptr<BitMap>&&) {}
  virtual void Draw() = 0;
  virtual ~BitMap() = default;
};

//defines a composable type Line.
class Line : public BitMap
{
public:
  virtual void Draw() override
  {
    std::cout << "Drawing a line" << std::endl;
  }

  ~Line() = default;

};

//defines a composable type Rectange.
class Rectange : public BitMap
{
public:
  virtual void Draw() override
  {
    std::cout << "Drawing a rectangle" << std::endl;
  }

  ~Rectange() = default;

};

//defines a composable type Text.
class Text : public BitMap
{
public:
  virtual void Draw() override
  {
    std::cout << "Drawing text" << std::endl;
  }

  ~Text() = default;

};

//defines a composable type Canvas.
class Canvas : public BitMap
{
private:
  std::vector<std::unique_ptr<BitMap>> elements;

public:
  virtual void Add(std::unique_ptr<BitMap> &&b) override
  {
    elements.emplace_back(std::forward<std::unique_ptr<BitMap>>(b));
  }

  virtual void Draw() override
  {
    for (auto&& element : elements)
    {
      element->Draw();
    }
  }

  ~Canvas() = default;

};

int main()
{
  auto line = std::make_unique<Line>();
  line->Draw();

  auto rectange = std::make_unique<Rectange>();
  rectange->Draw();
  
  auto text = std::make_unique<Text>();
  text->Draw();

  auto canvas = std::make_unique<Canvas>();
  
  canvas->Add(std::move(line));
  canvas->Add(std::move(rectange));
  canvas->Add(std::move(text));

  std::cout << "Drawing canvas" << std::endl;
  canvas->Draw();

  auto canvas2 = std::make_unique<Canvas>();

  //canvas itself is also composable.
  canvas2->Add(std::move(canvas));

  std::cout << "Drawing canvas 2" << std::endl;
  canvas2->Draw();

  return 0;
}