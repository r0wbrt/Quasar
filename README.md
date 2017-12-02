Note - This library is no longer maintained  as it was originally developed with the intention of creating a SDR radar. See https://github.com/r0wbrt/YASDRR for the realization of this goal.

About
=======

Quasar is a fork of the free and open source Aquila library. The main difference between 
Quasar and Aquila is templating. Quasar is designed to be a templated mostly headers only
library. The goal of Quasar is to allow any numeric type to be dropped in. Many algorithms
have been tested with both real (double) and comple (std::complex<double>) types. For
most core classes, it is as simple as specifying the type you wish to use as a template 
argument.

However, support for fixed based computation is still lacking and most 
algorithms assume floating point based numbers. Expanding support 
of the library to cover fixed point types is still under research.   


License
=======

The library is licensed under the Apache 2.0 license. A copy of the license
is distributed with the library in the NOTICE file.


Authors
=======

Quasar is maintained by Robert C. Taylor and uses code written by the following authors:

This library includes code from Aquila DSP libaray by Zbigniew Siciarz (zbigniew at siciarz dot net) and
window functions written by Uli Köhler.

This library includes code from Takuya Ooura's mathematical software packages,
which are available at http://www.kurims.kyoto-u.ac.jp/~ooura/.
