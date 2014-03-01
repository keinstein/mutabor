/* $Id: midifile.h,v 1.3 1991/11/03 21:50:50 piet Rel $ */
/* definitions for MIDI file parsing code */
/* Functions to be called while processing the MIDI file. */
extern int  (*Mf_getc)();
extern void  (*Mf_error)(char * s);
extern void  (*Mf_header)(int format, int ntrks, int division);
extern void (*Mf_starttrack)();
extern void (*Mf_endtrack)();
extern void (*Mf_on)(int chan, int pitch, int vol);
extern void (*Mf_off)(int chan, int pitch, int vol);
extern void (*Mf_pressure)(int chan, int pitch, int press);
extern void (*Mf_parameter)(int chan, int control, int value);
extern void (*Mf_pitchbend)(int chan, int lsb, int msb);
extern void (*Mf_program)(int chan, int program);
extern void (*Mf_chanpressure)(int chan, int press);
extern void (*Mf_sysex)(int leng, char *mess);
extern void (*Mf_arbitrary)(int leng, char *mess);
extern void (*Mf_metamisc)(int type, int leng, char *mess);
extern void (*Mf_seqnum)(int num);
extern void (*Mf_eot)();
extern void (*Mf_smpte)(int hr, int mn, int se, int fr, int ff);
extern void (*Mf_tempo)(long tempo);
extern void (*Mf_timesig)(int nn, int dd, int cc, int bb);
extern void (*Mf_keysig)(int sf, int mi);
extern void (*Mf_sqspecific)(int leng, char *mess);
extern void (*Mf_text)(int type, int leng, char *mess);

extern long Mf_currtime;
extern int Mf_nomerge;

/* definitions for MIDI file writing code */
extern int (*Mf_putc)(int c);
extern int (*Mf_wtrack)();
extern int (*Mf_wtempotrack)();
float mf_ticks2sec();
unsigned long mf_sec2ticks();
void mfwrite();
void mfread();

/* MIDI status commands most significant bit is 1 */
#define note_off         	0x80
#define note_on          	0x90
#define poly_aftertouch  	0xa0
#define control_change    	0xb0
#define program_chng     	0xc0
#define channel_aftertouch      0xd0
#define pitch_wheel      	0xe0
#define system_exclusive      	0xf0
#define delay_packet	 	(1111)

/* 7 bit controllers */
#define damper_pedal            0x40
#define portamento	        0x41 	
#define sostenuto	        0x42
#define soft_pedal	        0x43
#define general_4               0x44
#define	hold_2		        0x45
#define	general_5	        0x50
#define	general_6	        0x51
#define general_7	        0x52
#define general_8	        0x53
#define tremolo_depth	        0x5c
#define chorus_depth	        0x5d
#define	detune		        0x5e
#define phaser_depth	        0x5f

/* parameter values */
#define data_inc	        0x60
#define data_dec	        0x61

/* parameter selection */
#define non_reg_lsb	        0x62
#define non_reg_msb	        0x63
#define reg_lsb		        0x64
#define reg_msb		        0x65

/* Standard MIDI Files meta event definitions */
#define	meta_event		0xFF
#define	sequence_number 	0x00
#define	text_event		0x01
#define copyright_notice 	0x02
#define sequence_name    	0x03
#define instrument_name 	0x04
#define lyric	        	0x05
#define marker			0x06
#define	cue_point		0x07
#define channel_prefix		0x20
#define	end_of_track		0x2f
#define	set_tempo		0x51
#define	smpte_offset		0x54
#define	time_signature		0x58
#define	key_signature		0x59
#define	sequencer_specific	0x7f

/* Manufacturer's ID number */
#define Seq_Circuits (0x01) /* Sequential Circuits Inc. */
#define Big_Briar    (0x02) /* Big Briar Inc.           */
#define Octave       (0x03) /* Octave/Plateau           */
#define Moog         (0x04) /* Moog Music               */
#define Passport     (0x05) /* Passport Designs         */
#define Lexicon      (0x06) /* Lexicon 			*/
#define Tempi        (0x20) /* Bon Tempi                */
#define Siel         (0x21) /* S.I.E.L.                 */
#define Kawai        (0x41) 
#define Roland       (0x42)
#define Korg         (0x42)
#define Yamaha       (0x43)

/* miscellaneous definitions */
#define MThd 0x4d546864L
#define MTrk 0x4d54726bL
#define lowerbyte(x) ((unsigned char)(x & 0xff))
#define upperbyte(x) ((unsigned char)((x & 0xff00)>>8))
