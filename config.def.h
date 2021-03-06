/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static unsigned int snap	 = 32;	/* snap pixel */
static unsigned int gappih	 = 0;	/* horiz inner gap between windows */
static unsigned int gappiv	 = 0;	/* vert inner gap between windows */
static unsigned int gappoh	 = 0;	/* horiz outer gap between windows and screen edge */
static unsigned int gappov	 = 0;	/* vert outer gap between windows and screen edge */
static unsigned int borderpx	 = 3;	/* border pixel of windows */
static int swallowfloating	 = 0;	/* 1 means swallow floating windows by default */
static int smartgaps		 = 0;	/* 1 means no outer gap when there is only one window */
static int showbar		 = 1;	/* 0 means no bar */
static int topbar		 = 1;	/* 0 means bottom bar */
static char *fonts[]		 = {"monospace:size=12","NotoColorEmoji:pixelsize=12:antialias=true:autohint=true"};
static char normbgcolor[]	 = "#222222";
static char normbordercolor[]	 = "#444444";
static char normfgcolor[]	 = "#bbbbbb";
static char selfgcolor[]	 = "#eeeeee";
static char selbordercolor[]	 = "#770000";
static char selbgcolor[]	 = "#005577";
static char *colors[][3] = {
	[SchemeNorm] = {normfgcolor,normbgcolor,normbordercolor},
	[SchemeSel] = {selfgcolor,selbgcolor,selbordercolor},
};

static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
static Sp scratchpads[] = {
	{"spterm",spcmd1},
};

static const Rule rules[] = {
	{TERMCLASS,	NULL,		NULL,	0,		0,	1,	0,	-1},
	{TERMCLASS,	"bg",		NULL,	1 << 7,		0,	1,	0,	-1},
	{TERMCLASS,	"spterm",	NULL,	SPTAG(0),	1,	1,	0,	-1},
};


static float mfact	 = 0.55;/*factor of master area size*/
static int nmaster	 = 1;	/*number of clients in master area*/
static int resizehints	 = 0;	/*1 means respect size hints in tiled resizals*/
#define FORCE_VSPLIT 0
#include "vanitygaps.c"

static const Layout layouts[] = {
	/*symbol	Layout*/
	{"[]=",		tile},
	{"TTT",		bstack},
	{"[@]",		spiral},
	{"[\\]",	dwindle},
	{"[D]",		deck},
	{"[M]",		monocle},
	{"|M|",		centeredmaster},
	{">M>",		centeredfloatingmaster},
	{"><>",		NULL},
	{NULL,		NULL},
};

/*Key definitions*/
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{MODKEY,			KEY,	view,		{.ui = 1 << TAG}},\
	{MODKEY|ControlMask,		KEY,	toggleview,	{.ui = 1 << TAG}},\
	{MODKEY|ShiftMask,		KEY,	tag,		{.ui = 1 << TAG}},\
	{MODKEY|ControlMask|ShiftMask,	KEY,	toggletag,	{.ui = 1 << TAG}},

#define STACKKEYS(MOD,ACTION) \
	{MOD,	XK_j,	ACTION##stack,	{.i = INC(+1)}},\
	{MOD,	XK_k,	ACTION##stack,	{.i = INC(-1)}},\
	{MOD,	XK_v,	ACTION##stack,	{.i = 0}},\


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/*Xresources preferences to load at startup*/
ResourcePref resources[] = {
	{"color0",	STRING,	&normbordercolor},
	{"color8",	STRING,	&selbordercolor},
	{"color0",	STRING,	&normbgcolor},
	{"color4",	STRING,	&normfgcolor},
	{"color0",	STRING,	&selfgcolor},
	{"color4",	STRING,	&selbgcolor},
	{"borderpx",	INTEGER,&borderpx},
	{"snap",	INTEGER,&snap},
	{"showbar",	INTEGER,&showbar},
	{"topbar",	INTEGER,&topbar},
	{"nmaster",	INTEGER,&nmaster},
	{"resizehints",	INTEGER,&resizehints},
	{"mfact",	FLOAT,	&mfact},
	{"gappih",	INTEGER,&gappih},
	{"gappiv",	INTEGER,&gappiv},
	{"gappoh",	INTEGER,&gappoh},
	{"gappov",	INTEGER,&gappov},
	{"smartgaps",	INTEGER,&smartgaps},
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	STACKKEYS(MODKEY,focus)
	STACKKEYS(MODKEY|ShiftMask,push)

/*	mod	key	value*/
	TAGKEYS(XK_1,	0)
	TAGKEYS(XK_2,	1)
	TAGKEYS(XK_3,	2)
	TAGKEYS(XK_4,	3)
	TAGKEYS(XK_5,	4)
	TAGKEYS(XK_6,	5)
	TAGKEYS(XK_7,	6)
	TAGKEYS(XK_8,	7)
	TAGKEYS(XK_9,	8)

/*					Layouts					*/
	{MODKEY,		XK_t,	setlayout,	{.v = &layouts[0]}},/*tile*/
	{MODKEY|ShiftMask,	XK_t,	setlayout,	{.v = &layouts[1]}},/*bstack*/
	{MODKEY,		XK_y,	setlayout,	{.v = &layouts[2]}},/*spiral*/
	{MODKEY|ShiftMask,	XK_y,	setlayout,	{.v = &layouts[3]}},/*dwindle*/
	{MODKEY,		XK_u,	setlayout,	{.v = &layouts[4]}},/*deck*/
	{MODKEY|ShiftMask,	XK_u,	setlayout,	{.v = &layouts[5]}},/*monocle*/
	{MODKEY,		XK_i,	setlayout,	{.v = &layouts[6]}},/*centeredmaster*/
	{MODKEY|ShiftMask,	XK_i,	setlayout,	{.v = &layouts[7]}},/*centeredfloatingmaster*/

	{MODKEY,		XK_q,	killclient,	{0}},
	{MODKEY,		XK_a,	togglegaps,	{0}},
	{MODKEY|ShiftMask,	XK_a,	defaultgaps,	{0}},
	{MODKEY,		XK_s,	togglesticky,	{0}},
	{MODKEY,		XK_f,	togglefullscr,	{0}},
	{MODKEY,		XK_Tab,	togglesmartgaps,{0}},
	{MODKEY,		XK_o,	incnmaster,	{.i = +1}},
	{MODKEY|ShiftMask,	XK_o,	incnmaster,	{.i = -1}},
	{MODKEY,		XK_0,	view,		{.ui = ~0}},
	{MODKEY,		XK_h,	setmfact,	{.f = -0.05}},
	{MODKEY,		XK_l,	setmfact,	{.f = +0.05}},
	{MODKEY,		XK_w,	spawn,		SHCMD("$BROWSER >/dev/null 2>&1")},
	{MODKEY,		XK_p,	spawn,		SHCMD("mpc toggle")},
	{MODKEY|ShiftMask,	XK_w,	spawn,		SHCMD(TERMINAL " -e sudo nmtui")},
	{MODKEY|ShiftMask,	XK_p,	spawn,		SHCMD("mpc pause ; pauseallmpv")},

	{MODKEY,		XK_Return,	spawn,	SHCMD("samedir")},
	{MODKEY,		XK_comma,	spawn,	SHCMD("mpc prev")},
	{MODKEY,		XK_period,	spawn,	SHCMD("mpc next")},
	{MODKEY,		XK_d,		spawn,	SHCMD("dmenu_run")},
	{MODKEY,		XK_m,		spawn,	SHCMD(TERMINAL " -e ncmpcpp")},
	{MODKEY|ShiftMask,	XK_m,		spawn,	SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)")},
	{MODKEY,		XK_minus,	spawn,	SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)")},
	{MODKEY,		XK_equal,	spawn,	SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)")},
	{MODKEY,		XK_F4,		spawn,	SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)")},

	{MODKEY,		XK_b,		togglebar,	{0}},
	{MODKEY,		XK_space,	zoom,		{0}},
	{MODKEY|ShiftMask,	XK_space,	togglefloating,	{0}},
	{MODKEY,		XK_z,		incrgaps,	{.i = +3}},
	{MODKEY,		XK_x,		incrgaps,	{.i = -3}},
	{MODKEY,		XK_Left,	focusmon,	{.i = -1}},
	{MODKEY|ShiftMask,	XK_Left,	tagmon,		{.i = -1}},
	{MODKEY,		XK_Right,	focusmon,	{.i = +1}},
	{MODKEY|ShiftMask,	XK_Right,	tagmon,		{.i = +1}},
	{MODKEY|ShiftMask,	XK_Return,	togglescratch,	{.ui = 0}},
	{MODKEY,		XK_F3,		spawn,		SHCMD("displayselect")},


	{0,			XK_Print,	spawn,		SHCMD("maim $HOME/Documents/Pictures/pic-$(date '+%d%m%y-%H%M%S').png")},
	{MODKEY,		XK_Print,	spawn,		SHCMD("maim -s $HOME/Documents/Pictures/pic-$(date '+%d%m%y-%H%M%S').png")},
	{MODKEY|ShiftMask,	XK_Print,	spawn,		SHCMD("dmenurecord")},
	{MODKEY,		XK_Delete,	spawn,		SHCMD("dmenurecord kill")},



	{0,XF86XK_DOS,		spawn,SHCMD("samedir")},
	{0,XF86XK_WWW,		spawn,SHCMD("$BROWSER >/dev/null 2>&1")},
	{0,XF86XK_AudioPlay,	spawn,SHCMD("mpc play")},
	{0,XF86XK_AudioStop,	spawn,SHCMD("mpc stop")},
	{0,XF86XK_AudioPrev,	spawn,SHCMD("mpc prev")},
	{0,XF86XK_AudioNext,	spawn,SHCMD("mpc next")},
	{0,XF86XK_AudioPause,	spawn,SHCMD("mpc pause")},
	{0,XF86XK_Sleep,	spawn,SHCMD("sudo -A zzz")},
	{0,XF86XK_AudioRewind,	spawn,SHCMD("mpc seek -10")},
	{0,XF86XK_AudioForward,	spawn,SHCMD("mpc seek +10")},
	{0,XF86XK_Launch1,	spawn,SHCMD("xset dpms force off")},
	{0,XF86XK_AudioMedia,	spawn,SHCMD(TERMINAL " -e ncmpcpp")},
	{0,XF86XK_MonBrightnessUp,spawn,SHCMD("xbacklight -inc 10")},
	{0,XF86XK_MonBrightnessDown,spawn,SHCMD("xbacklight -dec 10")},
	{0,XF86XK_TouchpadOff,	spawn,SHCMD("synclient TouchpadOff=1")},
	{0,XF86XK_TouchpadOn,	spawn,SHCMD("synclient TouchpadOff=0")},
	{0,XF86XK_AudioMute,	spawn,SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)")},
	{0,XF86XK_AudioRaiseVolume,spawn,SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)")},
	{0,XF86XK_AudioLowerVolume,spawn,SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)")},
};

/*button definitions*/
/*click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin*/
static Button buttons[] = {
	{ClkTagBar,0,Button1,view,{0}},
	{ClkTagBar,MODKEY,Button1,tag,{0}},
	{ClkStatusText,0,Button1,sigdwmblocks,{.i = 1}},
	{ClkStatusText,0,Button2,sigdwmblocks,{.i = 2}},
	{ClkStatusText,0,Button3,sigdwmblocks,{.i = 3}},
	{ClkStatusText,0,Button4,sigdwmblocks,{.i = 4}},
	{ClkStatusText,0,Button5,sigdwmblocks,{.i = 5}},
	{ClkClientWin,MODKEY,Button4,incrgaps,{.i = +1}},
	{ClkClientWin,MODKEY,Button5,incrgaps,{.i = -1}},
	{ClkStatusText,ShiftMask,Button1,sigdwmblocks,{.i = 6}},
	{ClkStatusText,ShiftMask,Button3,spawn,SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h")},
};

