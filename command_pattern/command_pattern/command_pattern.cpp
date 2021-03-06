// command_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>

// Interface class for defining the structure of a command.
class Command
{
public:
  virtual void execute() = 0;
};


//actionable object that a command acts on.
class StockTrade
{
public:
  void buy()
  {
    std::cout << "buy stock" << std::endl;
  }

  void sell()
  {
    std::cout << "sell stock" << std::endl;
  }
};


//command to buy a stock.
class BuyOrder : public Command
{
private:
  std::shared_ptr<StockTrade> stock;

public:
  BuyOrder(std::shared_ptr<StockTrade> _stock) : stock(std::move(_stock)) {}

  virtual void execute() override
  {
    stock->buy();
  }
};


//command to sell a stock.
class SellOrder : public Command
{
private:
  std::shared_ptr<StockTrade> stock;

public:
  SellOrder(std::shared_ptr<StockTrade> _stock) : stock(std::move(_stock)) {}

  virtual void execute() override
  {
    stock->sell();
  }
};


//agent to accept and execute the commands.
class StockAgent
{
public:
  template<typename T>
  void order(std::unique_ptr<T>&& command)
  {
    static_assert(std::is_base_of<Command, T>::value);
    command->execute();
  }
};


int main()
{
  auto stock = std::make_shared<StockTrade>();
  auto buy1 = std::make_unique<BuyOrder>(stock);
  auto buy2 = std::make_unique<BuyOrder>(stock);
  auto sell1 = std::make_unique<SellOrder>(stock);
  auto sell2 = std::make_unique<SellOrder>(stock);

  auto agent = std::make_unique<StockAgent>();

  agent->order(std::move(buy1));
  agent->order(std::move(buy2));
  agent->order(std::move(sell1));
  agent->order(std::move(sell2));

  getchar();

  return 0;
}