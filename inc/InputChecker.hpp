#ifndef INPUTCHECKER_HPP
#define INPUTCHECKER_HPP

class InputChecker
{
private:
public:
  InputChecker(/* args */);
  virtual ~InputChecker();
  template <typename T>
  bool checkDatatype(T &input);
};

#endif INPUTCHECKER_HPP

