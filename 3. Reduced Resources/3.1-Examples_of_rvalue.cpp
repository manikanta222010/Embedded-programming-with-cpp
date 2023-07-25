int five= 5;
std::string a= std::string("Rvalue");
std::string b= std::string("R") +  std::string("value");
std::string c= a + b;
std::string d= std::move(b);
