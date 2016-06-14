#include "aquila/Exceptions.h"
#include "UnitTest++/UnitTest++.h"


SUITE(Exceptions)
{
    TEST(Exception)
    {
        try
        {
            throw Quasar::Exception("message");
        }
        catch (const Quasar::Exception& exc)
        {
            CHECK_EQUAL("message", exc.what());
        }
    }

    TEST(FormatException)
    {
        try
        {
            throw Quasar::FormatException("message");
        }
        catch (const Quasar::FormatException& exc)
        {
            CHECK_EQUAL("message", exc.what());
        }
    }

    TEST(ConfigurationException)
    {
        try
        {
            throw Quasar::ConfigurationException("message");
        }
        catch (const Quasar::ConfigurationException& exc)
        {
            CHECK_EQUAL("message", exc.what());
        }
    }
}
