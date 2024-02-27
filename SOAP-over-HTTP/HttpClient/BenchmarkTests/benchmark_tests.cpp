#include <iostream>
#include <benchmark/benchmark.h>
#include <../Domain/SoapMessageCreator.h>

int main(){
    Domain::InitializeLibrary();
    auto message{Domain::PrepareSimpleSoapMessage()};
    Domain::DeinitializeLibrary();
    std::cout<<"Message: " << message << std::endl;
    return 0;
}
