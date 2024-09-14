#include "pricinglibrary.h"

int main(int argc, char** argv)
{
    PricingLibrary::Initialize();
    PricingLibrary::Run();
    PricingLibrary::CleanUp();
    return 0;
}
