/* See LICENSE file for copyright and license details. */

#define BOTTOM_BAR_HEIGHT    13

/* appearance */

//static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
//static const char normbordercolor[] = "#444444";
//static const char normbgcolor[]     = "#222222";
//static const char normfgcolor[]     = "#bbbbbb";
//static const char selbordercolor[]  = "#005577";
//static const char selbgcolor[]      = "#005577";
//static const char selfgcolor[]      = "#eeeeee";
//static const unsigned int borderpx  = 1;        /* border pixel of windows */
//static const unsigned int snap      = 32;       /* snap pixel */
//static const Bool showbar           = True;     /* False means no bar */
//static const Bool topbar            = True;     /* False means bottom bar */


/* my appearance */

//static const char font[]            = "-misc-fixed-medium-r-semicondensed--13-100-100-100-c-60-iso8859-1";
static const char font[]            = "-truetype-pragmata-*-*-*--13-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#3b5998";
static const char normbgcolor[]     = "#3b5998";
static const char normfgcolor[]     = "#ffffff";
static const char selbordercolor[]  = "#3c3b37";
static const char selbgcolor[]      = "#3c3b37";
static const char selfgcolor[]      = "#b1d631";
static unsigned int borderpx        = 3;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static Bool showbar                 = True;     /* False means no bar */
static Bool topbar                  = True;     /* False means bottom bar */



/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "1 shells", "2 shells+", "3 shells++", "4 code", "5 web", "6 web+", "7 mail", "8 media", "9 /b/" };
//static unsigned int tagset[] = {1, 1}; /* after start, first tag is selected */


static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "MPlayer",  NULL,       NULL,       0,	  True,		 -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "TTT",      bstack },
 	{ "===",      bstackhoriz }
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 	= { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  	= { "urxvt", NULL };
static const char *webcmd[]	= { "firefox", NULL };
static const char *volup[]    	= { "volup", NULL };
static const char *voldwn[]    	= { "voldwn", NULL };
static const char *volmute[]    = { "volmute", NULL };
static const char *xlockcmd[] 	= { "xscreensaver-command", "-lock", NULL };

static Key keys[] = {
	/* modifier                     key        		function        argument */
	{ MODKEY,                       XK_space,  		spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      		spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_Page_Up,		spawn,          {.v = volup } },
	{ MODKEY,                       XK_Page_Down,   	spawn,          {.v = voldwn } },
	{ MODKEY,                       XK_End,    		spawn,          {.v = volmute } },
	{ MODKEY,                       XK_s,      		spawn,          {.v = xlockcmd } },
	{ MODKEY|ShiftMask,             XK_Return,     		spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      		togglebar,      {0} },
	{ MODKEY,                       XK_j,      		focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      		focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      		incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      		incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      		setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 		zoom,           {0} },
	{ MODKEY,                       XK_Tab,    		view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      		killclient,     {0} },
	{ MODKEY,                       XK_t,      		setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      		setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      		setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_p,	   		setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  		togglefloating, {0} },
	{ MODKEY,                       XK_0,     		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      		tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  		focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 		focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 		tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      		quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

