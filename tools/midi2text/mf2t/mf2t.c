/* $Id: mf2t.c,v 1.5 1995/12/14 20:20:10 piet Rel $ */
/*
 * mf2t
 * 
 * Convert a MIDI file to text.
 * 
 * 2005/09/21  I changed the usage of sys_errlist. Instead to use sys_errlist the program calls strerror.
 * vjs
 * 
 */

#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#include "midifile.h"
#include "mf2tfuncts.h"

static int TrkNr;
static int TrksToDo = 1;
static int Measure, M0, Beat, Clicks;
static long T0;

extern int arg_index;
extern char *arg_option;

/* internal functions - within this source file */
void initfuncs();
void prtime();
void prhex(char *, int);
void prtext(char *, int);
void printhelp(void);
int filegetc();

void error(char *);

/* options */

static int optFold 	= 0;		/* fold long lines */
static int optNotes = 0;		/* print notes as a-g */
static int optTimes = 0;		/* print time as Measure/beat/click */

static char *Onmsg  	= "On ch=%d n=%s v=%d\n";
static char *Offmsg 	= "Off ch=%d n=%s v=%d\n";
static char *PoPrmsg 	= "PoPr ch=%d n=%s v=%d\n";
static char *Parmsg 	= "Par ch=%d c=%d v=%d\n";
static char *Pbmsg  	= "Pb ch=%d v=%d\n";
static char *PrChmsg 	= "PrCh ch=%d p=%d\n";
static char *ChPrmsg 	= "ChPr ch=%d v=%d\n";

static FILE *F;


int main(argc,argv)
int argc;
char **argv;
{
	FILE *efopen();
	int flg;
	
	Mf_nomerge = 1;
	while (flg = crack (argc, argv, "F|f|BbNnTtVvMmHh", 0)) {
		switch (flg) {
		case 'f':
		case 'F':
			if (*arg_option)
				optFold = atoi(arg_option);
			else
				optFold = 80;
			break;
		case 'm':
		case 'M':
			Mf_nomerge = 0;
			break;
		case 'n':
		case 'N':
			optNotes++;
			break;
		case 't':
		case 'T':
		case 'b':
		case 'B':
			optTimes++;
			break;
		case 'v':
		case 'V':
			Onmsg  = "On ch=%d note=%s vol=%d\n";
			Offmsg = "Off ch=%d note=%s vol=%d\n";
			PoPrmsg = "PolyPr ch=%d note=%s val=%d\n";
			Parmsg = "Param ch=%d con=%d val=%d\n";
			Pbmsg  = "Pb ch=%d val=%d\n";
			PrChmsg = "ProgCh ch=%d prog=%d\n";
			ChPrmsg = "ChanPr ch=%d val=%d\n";
			break;
		case 'h':
		case 'H':
			printhelp();
			exit(0);
		case EOF:
			exit(1);
		}
	}
	if ( arg_index < argc )
		F = efopen(argv[arg_index++],"rb");
	else {
#ifdef SETMODE
	        setmode(fileno(stdin), O_BINARY);
		F = stdin;
#else
		F = fdopen(fileno(stdin),"rb");
#endif
	      }
	if (arg_index < argc &&
		!freopen (argv[arg_index],"w",stdout))
			error("Can't open output file");

	initfuncs();
	Mf_getc = filegetc;
	TrkNr = 0;
	Measure = 4;
	Beat = 96;
	Clicks = 96;
	T0 = 0;
	M0 = 0;
	mfread();
	if (ferror(F)) error("Output file error");
	fclose(F);
	exit(0);
}

int filegetc()
{
	int c;
	
	c = getc(F);
	
	// printf("precteno %d, 0x%x\n", precteno, c);
	return(c);
}


FILE *
efopen(name,mode)
char *name;
char *mode;
{
	FILE *f;
	extern int errno;

	if ( (f=fopen(name,mode)) == NULL ) {
		(void) fprintf(stderr,"*** ERROR *** Cannot open '%s'!\n",name);
		(void) fprintf(stderr,"************* Reason: %d\n", errno);      // vjs - my change
		exit(1);
	}
	return(f);
}

void error(s)
char *s;
{
        if (TrksToDo <= 0)
	    	fprintf(stderr,"Error: Garbage at end: %s\n",s);
	else
	    fprintf(stderr,"Error: %s\n",s);
}

	
char *
mknote(pitch)
int pitch;
{
	static char * Notes [] =
		{ "c", "c#", "d", "d#", "e", "f", "f#", "g",
		  "g#", "a", "a#", "b" };
	static char buf[5];
	if ( optNotes )
		sprintf (buf, "%s%d", Notes[pitch % 12], pitch/12);
	else
		sprintf (buf, "%d", pitch);
	return buf;
}

void myheader(format,ntrks,division)
int format, ntrks, division;
{
	if (division & 0x8000) { /* SMPTE */
	    optTimes = 0;		 /* Can't do beats */
	    printf("MFile %d %d %d %d\n",format,ntrks,
	    			-((-(division>>8))&0xff), division&0xff);
	} else
	    printf("MFile %d %d %d\n",format,ntrks,division);
	if (format > 2) {
		fprintf(stderr, "Can't deal with format %d files\n", format);
		exit (1);
	}
	Beat = Clicks = division;
	TrksToDo = ntrks;
}

void mytrstart()
{
	printf("MTrk\n");
	TrkNr ++;
}

void mytrend()
{
	printf("TrkEnd\n");
	--TrksToDo;
}

void mynon(chan,pitch,vol)
int chan, pitch, vol;
{
	prtime();
	printf(Onmsg,chan+1,mknote(pitch),vol);
}

void mynoff(chan,pitch,vol)
int chan, pitch, vol;
{
	prtime();
	printf(Offmsg,chan+1,mknote(pitch),vol);
}

void mypressure(chan,pitch,press)
int chan, pitch, press;
{
	prtime();
	printf(PoPrmsg,chan+1,mknote(pitch),press);
}

void myparameter(chan,control,value)
int chan, control, value;
{
	prtime();
	printf(Parmsg,chan+1,control,value);
}

void mypitchbend(chan,lsb,msb)
int chan, lsb, msb;
{
	prtime();
	printf(Pbmsg,chan+1,128*msb+lsb);
}

void myprogram(chan,program)
int chan, program;
{
	prtime();
	printf(PrChmsg,chan+1,program);
}

void mychanpressure(chan,press)
int chan, press;
{
	prtime();
	printf(ChPrmsg,chan+1,press);
}

void mysysex(leng,mess)
int leng;
char *mess;
{
	prtime();
	printf("SysEx");
	prhex(mess, leng);
}

void mymmisc(type,leng,mess)
int type, leng;
char *mess;
{
	prtime();
	printf("Meta 0x%02x",type);
	prhex(mess, leng);
}

void mymspecial(leng,mess)
int leng;
char *mess;
{
	prtime();
	printf("SeqSpec");
	prhex(mess, leng);
}

void mymtext(type,leng,mess)
int type, leng;
char *mess;
{
	static char *ttype[] = {
		NULL,
		"Text",		/* type=0x01 */
		"Copyright",	/* type=0x02 */
		"TrkName",
		"InstrName",	/* ...       */
		"Lyric",
		"Marker",
		"Cue",		/* type=0x07 */
		"Unrec"
	};
	int unrecognized = (sizeof(ttype)/sizeof(char *)) - 1;

	prtime();
	if ( type < 1 || type > unrecognized )
		printf("Meta 0x%02x ",type);
	else if (type == 3 && TrkNr == 1)
		printf("Meta SeqName ");
	else
		printf("Meta %s ",ttype[type]);
	prtext (mess, leng);
}

void mymseq(num)
int num;
{
	prtime();
	printf("SeqNr %d\n",num);
}

void mymeot()
{
	prtime();
	printf("Meta TrkEnd\n");
}

void mykeysig(sf,mi)
int sf, mi;
{
	prtime();
	printf("KeySig %d %s\n", (sf>127?sf-256:sf), (mi?"minor":"major"));
}

void mytempo(tempo)
long tempo;
{
	prtime();
	printf("Tempo %ld\n",tempo);
}

void mytimesig(nn,dd,cc,bb)
int nn, dd, cc, bb;
{
	int denom = 1;
	while ( dd-- > 0 )
		denom *= 2;
	prtime();
	printf("TimeSig %d/%d %d %d\n",
		nn,denom,cc,bb);
	M0 += (Mf_currtime-T0)/(Beat*Measure);
	T0 = Mf_currtime;
	Measure = nn;
	Beat = 4 * Clicks / denom;
}

void mysmpte(hr,mn,se,fr,ff)
int hr, mn, se, fr, ff;
{
	prtime();
	printf("SMPTE %d %d %d %d %d\n",
		hr,mn,se,fr,ff);
}

void myarbitrary(leng,mess)
int leng;
char *mess;
{
	prtime();
	printf("Arb",leng);
	prhex (mess, leng);
}

void prtime()
{
	if (optTimes) {
		long m = (Mf_currtime-T0)/Beat;
		printf ("%ld:%ld:%ld ",
			m/Measure+M0, m%Measure, (Mf_currtime-T0)%Beat);
	} else
		printf("%ld ",Mf_currtime);
}

void prtext(p, leng)
char *p; int leng;
{
	int n, c;
	int pos = 25;
	
	printf("\"");
	for ( n=0; n<leng; n++ ) {
		c = *p++;
		if (optFold && pos >= optFold) {
			printf ("\\\n\t");
			pos = 13;	/* tab + \xab + \ */
			if (c == ' ' || c == '\t') {
				putchar ('\\');
				++pos;
			}
		}
		switch (c) {
		case '\\':
		case '"':
			printf ("\\%c", c);
			pos += 2;
			break;
		case '\r':
			printf ("\\r");
			pos += 2;
			break;
		case '\n':
			printf ("\\n");
			pos += 2;
			break;
		case '\0':
			printf ("\\0");
			pos += 2;
			break;
		default:
			if (isprint(c)) {
				putchar(c);
				++pos;
			} else {
				printf("\\x%02x" , c);
				pos += 4;
			}
		}
	}
	printf("\"\n");
}

void prhex(p, leng)
char *p; int leng;
{
	int n;
	int pos = 25;
	char *ptr = p;
	
	for ( n=0; n<leng; n++,ptr++ ) {
		if (optFold && pos >= optFold) {
			printf("\\\n\t%02x" , (unsigned char)(*ptr));
			pos = 14;	/* tab + ab + " ab" + \ */
		}
		else {
			printf(" %02x" , (unsigned char)(*ptr));
		}
	}
	printf("\n");
}

void printhelp(void)
{
	printf("\nUsage:\n\n");
	printf("\tmf2t [-mntvh] [-f[n]] [midifile [textfile]]\n\n");
	printf("\t\ttranslate midifile to textfile.\n\n");
	printf("\tWhen textfile is not given, the text is written to standard output.\n");
	printf("\tWhen midifile is not given it is read from standard input. The meaning\n");
	printf("\tof the options is:\n\n");
	printf("\t-m\tmerge partial sysex into a single sysex message\n");
	printf("\t-n\twrite notes in symbolic rather than numeric form.\n");
	printf("\t\t A-C optionally followed by # (sharp) followed by octave number.\n");
	printf("\t-b\tor\n");
	printf("\t-t\tevent times are written as bar:beat:click rather than a click number\n");
	printf("\t-v\tuse a slightly more verbose output\n");
	printf("\t-f<n>	fold long text and hex entries into more lines <n>=line length\n");
	printf("\t	   (default 80).\n");
	printf("\t-h\tprint this help text.\n");
}


void initfuncs()
{
	Mf_error 		=  error;
	Mf_header 		=  myheader;
	Mf_starttrack 	=  mytrstart;
	Mf_endtrack 	=  mytrend;
	Mf_on 			=  mynon;
	Mf_off 			=  mynoff;
	Mf_pressure 	=  mypressure;
	Mf_parameter 	=  myparameter;
	Mf_pitchbend 	=  mypitchbend;
	Mf_program 		=  myprogram;
	Mf_chanpressure =  mychanpressure;
	Mf_sysex 		=  mysysex;
	Mf_metamisc 	=  mymmisc;
	Mf_seqnum 		=  mymseq;
	Mf_eot 			=  mymeot;
	Mf_timesig 		=  mytimesig;
	Mf_smpte 		=  mysmpte;
	Mf_tempo 		=  mytempo;
	Mf_keysig 		=  mykeysig;
	Mf_sqspecific 	=  mymspecial;
	Mf_text 		=  mymtext;
	Mf_arbitrary 	=  myarbitrary;
}
