#include <iostream>
#include "swigmod.h"

class MERC : public Language
{
public:
    void main(int argc, char *argv[]) override
    {
        /* Set language-specific subdirectory in SWIG library */
        SWIG_library_directory("merc");

        /* Set language-specific preprocessing symbol */
        Preprocessor_define("SWIGMERC 1", 0);

        /* Set language-specific configuration file */
        SWIG_config_file("merc.swg");
    }

    int top(Node *n) override
    {
        String* module{ Getattr(n, "name") };
        String* outfile{ Getattr(n, "outfile") };

        Printf(stdout, "Processing module %s...\n", module);

        f_begin = NewFile(outfile, "w", SWIG_output_files());
        if (!f_begin)
        {
          FileErrorDisplay(outfile);
          Exit(EXIT_FAILURE);
        }
        f_runtime = NewString("");
        f_init = NewString("");
        f_header = NewString("");
        f_wrappers = NewString("");

        Swig_register_filebyname("begin", f_begin);
        Swig_register_filebyname("header", f_header);
        Swig_register_filebyname("wrapper", f_wrappers);
        Swig_register_filebyname("runtime", f_runtime);
        Swig_register_filebyname("init", f_init);

        Swig_banner(f_begin);

        Language::top(n);

        Dump(f_runtime, f_begin);
        Dump(f_header, f_begin);
        Dump(f_wrappers, f_begin);
        Wrapper_pretty_print(f_init, f_begin);

        Delete(f_runtime);
        Delete(f_header);
        Delete(f_wrappers);
        Delete(f_init);
        Delete(f_begin);

        return SWIG_OK;
    }

    int functionHandler(Node* n) override
    {
        return SWIG_OK;
    }

    int classHandler(Node* n) override
    {
        String* name{ Getattr(n, "sym:name") };
        Printf(f_wrappers, "class: %s\n", name);
        return SWIG_OK;
    }
private:
    File *f_begin;
    File *f_runtime;
    File *f_header;
    File *f_wrappers;
    File *f_init;
};

extern "C" Language* swig_merc(void)
{
    return new MERC();
}
