%module foo

namespace merc
{
    template<typename T>
    struct ScriptGen {};
}

struct Foo
{
    Steinberg::tresult addBar(merc::ActionData& actionData, Timing timing)
    {
        return 0;
    }
};

%template(Foo) merc::ScriptGen<Foo>;

int foo(int a, int b)
{
    return a + b;
}
