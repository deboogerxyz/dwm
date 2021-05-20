/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 4;        /* horiz inner gap between windows */
static unsigned int gappiv    = 4;        /* vert inner gap between windows */
static unsigned int gappoh    = 8;        /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 8;        /* vert outer gap between windows and screen edge */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int user_bh            = 25;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static char font[]            = "monospace:pixelsize=12:antialias=true:autohint=true";
static char fontalt[]         = "JoyPixels:pixelsize=10:antialias=true:autohint=true";
static const char *fonts[]    = { font, fontalt };
static char bgcol[]   = "#222222";
static char bordercol[]       = "#444444";
static char fgcol[]   = "#bbbbbb";
static char selfgcol[]= "#eeeeee";
static char selbordercol[]    = "#005577";
static char selbgcol[]= "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fgcol,     bgcol,     bordercol },
	[SchemeSel]  = { selfgcol,  selbgcol,  selbordercol  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, OPAQUE,   borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ TERMCLASS, NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "﬿",	tile },				/* Default: Master on left, slaves on right */
	{ "侀",	bstack },			/* Master on top, slaves on bottom */

	{ "",	spiral },			/* Fibonacci spiral */
	{ "",	dwindle },			/* Decreasing in size right and leftward */

	{ "[D]", deck },			/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]", monocle },			/* All windows on top of eachother */

	{ "|M|", centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>", centeredfloatingmaster },	/* Same but master floats */

	{ "",	NULL },				/* no layout function means floating behavior */
	{ NULL, NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "fontalt",            STRING,  &fontalt },
		{ "background",         STRING,  &bgcol },
		{ "color0",             STRING,  &bordercol },
		{ "foreground",         STRING,  &fgcol },
		{ "color0",             STRING,  &selfgcol },
		{ "color5",             STRING,  &selbgcol },
		{ "color5",             STRING,  &selbordercol },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          	INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "swallowfloating",    INTEGER, &swallowfloating },
		{ "barheight",          INTEGER, &user_bh },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = +0.25} },
	{ MODKEY,			XK_z,      incrgaps,	   {.i = +3 } },
	{ MODKEY,			XK_x,      incrgaps,	   {.i = -3 } },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,			XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,      setlayout,      {.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,      setlayout,      {.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,      setlayout,      {.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,      setlayout,      {.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,      setlayout,      {.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,      setlayout,      {.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,      setlayout,      {.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Left,   focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_e,      spawn,          SHCMD(TERMINAL " -e neomutt") },
	{ MODKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e lf") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY,                       XK_grave,  spawn,          SHCMD("dmenuunicode") },
	{ MODKEY,			XK_p,      spawn,          SHCMD("mpc toggle; kill -40 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("mpc pause; kill -40 $(pidof dwmblocks)") },
	{ MODKEY,			XK_bracketleft,		spawn,		SHCMD("mpc seek -10; kill -40 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_bracketleft,		spawn,		SHCMD("mpc seek -60; kill -40 $(pidof dwmblocks)") },
	{ MODKEY,			XK_bracketright,	spawn,		SHCMD("mpc seek +10; kill -40 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_bracketright,	spawn,		SHCMD("mpc seek +60; kill -40 $(pidof dwmblocks)") },
	{ MODKEY,			XK_comma,	spawn,		SHCMD("mpc prev; kill -40 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_comma,	spawn,		SHCMD("mpc seek 0%; kill -40 $(pidof dwmblocks)") },
	{ MODKEY,			XK_period,	spawn,		SHCMD("mpc next; kill -40 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_period,	spawn,		SHCMD("mpc repeat; kill -40 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_q,		spawn,		SHCMD("sysact") },
	{ MODKEY,                       XK_F1,          spawn,          SHCMD("dmenumount") },
	{ MODKEY,                       XK_F2,          spawn,          SHCMD("dmenuumount") },
	{ MODKEY,                       XK_F3,          spawn,          SHCMD(TERMINAL " -e pulsemixer") },
	{ MODKEY,                       XK_F4,          spawn,          SHCMD("passmenu") },
	{ MODKEY,                       XK_F5,     xrdb,           {0} },
	{ MODKEY,			XK_s,	spawn,		SHCMD("screen") },
	{ MODKEY|ShiftMask,		XK_s,	spawn,		SHCMD("screensel") },
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3") },
	{ 0, XF86XK_AudioMicMute,	spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev; kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next; kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause; kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc play; kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop; kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10; kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10; kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock") },
	{ 0, XK_Print,			spawn,		SHCMD("screen") },
	{ ShiftMask, XK_Print,		spawn,		SHCMD("screensel") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

