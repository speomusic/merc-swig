%module foo

namespace merc
{
    struct ScriptGen
    {
        
    };
}

struct Foo : merc::ScriptGen
{
    Steinberg::tresult addBar(merc::ActionData& actionData, Timing timing);
};

int foo(int a, int b)
{
    return a + b;
}
