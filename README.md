# Msieve-trial


大数分解

This guide is designed to help experienced computer users who are beginners to factoring numbers larger than 90 digits with the Number Field Sieve (NFS) algorithm.  It will guide you on how to use the GGNFS and MSIEVE software tools to accomplish this. 

For numbers smaller than 90 digits, the Quadratic Sieve (QS) should be used with such programs as MSIEVE or YAFU.  It is important to choose a reasonable factoring algorithm for the size of number you are attempting to factor.  For example, the 100 digit integer below took almost 80 days to factor using the ECM algorithm, while GNFS takes only hours.  Similarly, small numbers should be factored with something other than GNFS such as ECM or QS.

This guide shows an example of how to factor the following 100 digit integer using the General Number Field Sieve (GNFS) with Brian Gladman's factmsieve.py python script which uses both ggnfs and msieve tools:
2881039827457895971881627053137530734638790825166127496066674320241571446494762386620442953820735453

If you are looking for the older guide that uses the factmsieve.pl perl script you can still find it here.

Note: It is important to choose a reasonable factoring algorithm for the size of number you are attempting to factor.  For example, this same 100 digit integer took almost 80 days to factor using the ECM algorithm.

Step 1 - Download the Required Software

Obtain the GGNFS binaries.  If you are using Windows you will need version SVN 374 or newer, pre-compiled GGNFS binaries can are available from this web site.  If you are using Linux or some form of UNIX, you need to download the source code and compile it yourself, or use a 64bit Linux Binary.

Obtain the latest MSIEVE binaries (v1.43 or newer) and overwrite the msieve that comes with ggnfs.  If you are using Windows, pre-compiled MSIEVE binaries can are available from this web site.  If you are using Linux or some form of UNIX, you need to download the source code and compile it yourself.

Obtain the latest version of Brian Gladman's factmsieve.py script.

You will need PYTHON v2.6 or later installed on your system to run the factmsieve.py script.  For Windows users, you can download a 32bit or 64bit installer while Linux/UNIX users will need to download the source code and compile or install a python packge from your distribution.

If you need help with GGNFS in general, you can try searching for an answer or posting in the GGNFS Message Board.

NOTE: If you are not capable of completing the stages of Step 1, stop now, you probably do not have the technical skill to complete the rest.


Step 2 - Install and Configure the Software

After you have downloaded or compiled the GGNFS binaries, copy them to a directory on your system such as: C:\ggnfs or /ggnfs
The GGNFS distribution contains an older version of msieve, you should now copy your newly downloaded or compiled msieve binary over the old one in: C:\ggnfs or /ggnfs
Install the python 2.6 or later distribution that you downloaded.  Copy your newly downloaded factmsieve.py file to the ggnfs directory:  C:\ggnfs or /ggnfs

Your ggnfs directory (C:\ggnfs or /ggnfs) should now contain the following files (UNIX users will not have an .exe extension for the executables):
def-nm-params.txt
def-par.txt
factLat.pl
factMsieve.pl
factmsieve.py
ggnfs-doc.pdf
gnfs-lasieve4I11e.exe
gnfs-lasieve4I12e.exe
gnfs-lasieve4I13e.exe
gnfs-lasieve4I14e.exe
gnfs-lasieve4I15e.exe
gnfs-lasieve4I16e.exe
makefb.exe
matbuild.exe
matprune.exe
matsolve.exe
msieve.exe
pol51m0b.exe
pol51m0n.exe
pol51opt.exe
polyselect.exe
procrels.exe
sieve.exe
sqrt.exe

Change to your ggnfs directory (C:\ggnfs or cd /ggnfs) and create a working directory called example for your factoring job.  You should now have a directory called:  C:\ggnfs\example or /ggnfs/example

Use your favourite text editor to edit the factmsieve.py file.  Windows users may want to try Notepad++ or Crimson Editor.  You will need to modify several lines in factMsieve.py to configure the script for your system.  Make the changes listed below.

Change lines 63-64 from:
# Set binary directory paths
GGNFS_PATH = 'C:/Users/brg\Documents/Visual Studio 2015/Projects/ggnfs/bin/x64/Release'
MSIEVE_PATH = 'C:/Users/brg/Documents/Visual Studio 2015/Projects/msieve/bin/x64/Release'

to:

# Set binary directory paths
GGNFS_PATH = '../'
MSIEVE_PATH = '../'

Change line 67 from:
NUM_CPUS = 4
to whatever the # of CPUs you want to use for the factoring.  On a dual-core system you can choose 1 or 2, on a quad-core 1, 2, 3, 4:
NUM_CPUS = 4

Note:  Only 1 CPU is used for the polynomial, filtering, and square root phases, while NUM_CPUS is used for sieving and linear algebra.

By default, factmsieve.py will use msieve for polynomial selection.  Normal users should leave this setting alone.  If for some reason you would like to use the pol51 polynomial selection tool change lines 89-90 from:
USE_KLEINJUNG_FRANKE_PS = False
USE_MSIEVE_POLY = True
to:
USE_KLEINJUNG_FRANKE_PS = True
USE_MSIEVE_POLY = False

If you are using the GPU enabled version of msieve and want to enable polynomial selection using the GPU, change line 70 to ensure it says:
USE_CUDA = True
if you are not using a GPU, please ensure it says:
USE_CUDA = False

Ensure on line 104 that your msieve executable is properly named if you are using something other than 'msieve':
MSIEVE = 'msieve'

Save the changes to factMsieve.py and proceed to the next step.


Step 3 - Polynomial Selection

The NFS algorithm uses a 3 phase method, the first being polynomial selection, then sieving, and finally linear algebra.  Before factoring can begin, a polynomial must be selected.  The factmsieve.py script will run the appropriate tool to select one for you.

Windows users should open a Command Prompt and UNIX users should open a shell.  Change to your working directory (cd C:\ggnfs\example or cd /ggnfs/example).  In your working directory, create a text file called example.n and inside that file paste your number to factor, we will use the 100 digit example number and place "n: " in front so the file contains:
n: 2881039827457895971881627053137530734638790825166127496066674320241571446494762386620442953820735453

Windows users can start the factoring process with the factMsieve.py python script using this command in a Command Prompt from your working directory:
..\factMsieve.py example
UNIX users can start the factoring process using this command in a shell from your working directory:
../factMsieve.py example

This will call the msieve or pol51 tools to select a polynomial for the number in example.n. The output should look something like:

-> ________________________________________________________________
-> | Running factmsieve.py, a Python driver for MSIEVE with GGNFS |
-> | sieving support. It is Copyright, 2010, Brian Gladman and is |
-> | a conversion of factmsieve.pl that is Copyright, 2004, Chris |
-> | Monico.          This is version 0.1, dated 01 January 2010. |
-> |______________________________________________________________|
-> This is client 1 of 1
-> Using 2 threads
-> Working with NAME = example
-> Error: Polynomial file example.poly does not exist!
-> Found n = 2881039827457895971881627053137530734638790825166127496066674320241571446494762386620442953820735453.
-> Attempting to run polyselect...
-> msieve -s example.dat -l example.log -i example.ini -nf example.fb -v -np


Msieve v. 1.43
Tue Jan 12 13:39:36 2010
random seeds: 61377b88 b30ac047
factoring 2881039827457895971881627053137530734638790825166127496066674320241571446494762386620442953820735453 (100 digits)
searching for 15-digit factors
commencing number field sieve (100-digit input)
commencing number field sieve polynomial selection
time limit set to 0.35 hours
searching leading coefficients from 1 to 6474027
deadline: 5 seconds per coefficient
coeff 60-600 6717750 8733074 8733075 11352997 lattice 3130022
p 6717750 8733074 8733075 11352997 lattice 3130022
batch 5000 8176351


For this example number, polynomial selection took approximately 0.35 hours, after which the python script will automatically start the next steps for you.

If you already have a polynomial, you can also use the factmsieve.py script to complete the final 2 stages of the NFS algorithm.  If you created your polynomial with msieve, copy the file example.fb to your working directory (C:\ggnfs\example or /ggnfs/example).  If you used the pol51 software, copy the file example.poly to your working working directory (C:\ggnfs\example or /ggnfs/example).  Whichever method you used the select a polynomial, you can start factmsieve.py using the same command as above (..\factMsieve.py example or ../factMsieve.py example), if it sees an example.fb or example.poly file present in the working directory it will start sieving and skip the polynomial selection step.

Step 4 - Sieving and Linear Algebra

The final 2 phases of the NFS algorithm are taken care of for you by the factmsieve.py python script.  After a polynomial has been selected, the script will automatically start the siever.

The output of the sieving phase will look something like this:

polynomial selection complete
R0: -2000270008852372562401653
R1:  67637130392687
A0: -315744766385259600878935362160
A1:  76498885560536911440526
A2:  19154618876851185
A3: -953396814
A4:  180
skew 7872388.07, size 9.334881e-014, alpha -5.410475, combined = 1.161232e-008
elapsed time 00:26:02
-> Selected default factorization parameters for 100 digit level.
-> Selected lattice siever: gnfs-lasieve4I12e
-> Creating param file to detect parameter changes...
-> Q0 = 900000, QSTEP = 100000.
-> making sieve job for q from 900000 to 950000 as file example.job.T0.
-> making sieve job for q from 950000 to 1000000 as file example.job.T1.
-> Lattice sieving algebraic q-values from q = 900000 to 1000000.
-> gnfs-lasieve4I12e -k -o spairs.out.T0 -v -n0 -a example.job.T0
-> gnfs-lasieve4I12e -k -o spairs.out.T1 -v -n1 -a example.job.T1
FBsize 71421+0 (deg 4), 135071+0 (deg 1)
total yield: 102881, q=961529 (0.00323 sec/rel)
If you need to stop your job before it is complete, press CTRL-C and wait a few seconds for the siever to end gracefully.  The script will create a file called example.job.resume which should allow you to restart where you left off by running the same command as before from your working directory.  To continue factoring from where you left off, run:
..\factMsieve.py example or ../factMsieve.py example

After reaching an estimated minimum number of relations, the script will run msieve to see if enough relations have been collection to perform the linear algebra phase.  If not, sieving will automatically continue.  At some point, enough relations will be available and the script will automatically call msieve to perform the final linear algebra steps.  Once this is complete, the factors will be shown.  For our example number, roughly 4.7 million relations were needed and took around 8 hours of sieving on 1 processor of a Pentium4 3 GHz machine (4 hours with 2 CPUs).  Make sure you have enough free disk space as the relations take up a lot of room; the 4.7 millions relations and intermediate files used 650 MB of space.  The msieve program was then automatically called to do the linear algebra which took about 30 minutes and the results will look something like this:

<some data snipped>
.
.
commencing square root phase
reading relations for dependency 1
read 99087 cycles
cycles contain 319676 unique relations
read 319676 relations
multiplying 319676 relations
multiply complete, coefficients have about 12.58 million bits
initial square root is modulo 16887931
reading relations for dependency 2
read 98959 cycles
cycles contain 319048 unique relations
read 319048 relations
multiplying 319048 relations
multiply complete, coefficients have about 12.55 million bits
initial square root is modulo 16385419
reading relations for dependency 3
read 99422 cycles
cycles contain 320846 unique relations
read 320846 relations
multiplying 320846 relations
multiply complete, coefficients have about 12.62 million bits
initial square root is modulo 17930069
reading relations for dependency 4
read 98881 cycles
cycles contain 319162 unique relations
read 319162 relations
multiplying 319162 relations
multiply complete, coefficients have about 12.56 million bits
initial square root is modulo 16475743
reading relations for dependency 5
read 99112 cycles
cycles contain 319176 unique relations
read 319176 relations
multiplying 319176 relations
multiply complete, coefficients have about 12.56 million bits
initial square root is modulo 16482517
sqrtTime: 647
prp45 factor: 618162834186865969389336374155487198277265679
prp55 factor: 4660648728983566373964395375209529291596595400646068307
elapsed time 00:10:49
-> Computing 1.26333e+09 scale for this machine...
-> procrels -speedtest> PIPE
Scaled time: 3.24 units (timescale= 0.749).
Factorization summary written to g100-example.txt

As you can see from the output, the example number had 2 probable prime (prp) factors, one 45 digits (618162834186865969389336374155487198277265679) and the other 55 digits (4660648728983566373964395375209529291596595400646068307).  You can verify your results by multiplying the two factors together and confirm they equal the original number you were trying to factor.


Step 5 - Enjoy the Factors

Congrats you have just finished factoring your integer and now you are done.  Enjoy.  Remember that factoring larger numbers will take longer to select a good polynomial, sieve, and require more time and memory for the linear algebra stages.  Factoring a 155 digit number for example using GNFS will take months on a quad-core PC.  

SNFS Factoring - Special Number Field Sieve

You can also use GGNFS and MSIEVE to factor numbers using the Special Number Field Sieve (SNFS) which is beyond the scope of this guide.  Details about SNFS polynomial selection are available.  Several programs are available to generate SNFS polynomials for some special numbers, such as Homogenous Cunninghams, Cunninghams, and XYYX that you might need to compile yourself.  Create the polynomial file for the SNFS number you want to factor, and instead of using "type: gnfs" you need to use "type: snfs".  The rest of the instructions for factoring using SNFS should be similar to GNFS.
