/* See LICENSE file for copyright and license details. */

#include "colors/erosion.h"

/* appearance */
static const char font[]            = "-*-terminus-medium-r-normal--12-*-*-*-*-*-*-*";
static const char normbordercolor[] = base03;
static const char normbgcolor[]     = base02;
static const char normfgcolor[]     = base01;
static const char selbordercolor[]  = base1;
static const char selbgcolor[]      = base2;
static const char selfgcolor[]      = base3;

static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int tileborder= 12;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "term", "web", "doc", "voip", "misc", "video",
    "music", "chat", "mail" };

static const char java_name[] = "net-sourceforge-jnlp-runtime-Boot";
static const char nmon_name[] = "wicd-curses";
static const char vcon_name[] = "alsamixer";
static const char mail_inst[] = "www.gmail.com";
static const char music_inst[] = "play.spotify.com";
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Chromium", "chromium", NULL,       1 << 1,       False,       -1 },
	{ "Dwb",      "dwb",      NULL,       1 << 1,       False,       -1 },
	{ "Zathura",  NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Mumble",   NULL,       NULL,       1 << 3,       True,        -1 },
	{ NULL,       NULL,       "mutt",     1 << 8,       False,       -1 },
    { java_name,  NULL,       NULL,       1 << 5,       True,        -1 },
	{ NULL,       NULL,       "Steam",    1 << 4,       False,       -1 },
	{ "Steam",    NULL,       NULL,       1 << 4,       False,       -1 },
	{ "Vlc",      "vlc",      NULL,       1 << 5,       False,       -1 },
	{ "hl2_linux",NULL,       NULL,       1 << 5,       True,        -1 },
	{ "Chromium", music_inst, NULL,       1 << 6,       False,       -1 },
	{ "Skype",    NULL,       NULL,       1 << 7,       False,       -1 },
	//{ "Chromium", mail_inst,  NULL,       1 << 8,       False,       -1 },
	{ "sxiv",     NULL,       NULL,       0,            True,        -1 },
	{ NULL,       NULL,       nmon_name,  0,            True,        -1 },
	{ NULL,       NULL,       vcon_name,  0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False;/* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char term[]        = "urxvtc";
static const char *termcmd[]    = { term, NULL };
static const char *mailcmd[]    = { "dwb", "-Rn", mail_inst, NULL };
static const char *volcmd[]     = { term, "-e", vcon_name, NULL };
static const char *netmoncmd[]  = { term, "-e", nmon_name, NULL };
static const char *sysmoncmd[]  = { term, "-e", "htop", NULL };
static const char *browsercmd[] = { "dwb", "-R", NULL };
static const char *logout[]     = { "pkill", "-9", "startdwm", NULL };
static const char *spotify[]    = { "chromium", "--app=http://play.spotify.com",
    NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_F12,    togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_equal,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_F9,     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_F10,    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_F11,    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ WINKEY,                       XK_b,      spawn,          {.v = browsercmd } },
	{ WINKEY,                       XK_m,      spawn,          {.v = mailcmd } },
	{ WINKEY,                       XK_v,      spawn,          {.v = volcmd } },
	{ WINKEY,                       XK_w,      spawn,          {.v = netmoncmd } },
	{ WINKEY,                       XK_t,      spawn,          {.v = sysmoncmd } },
	{ WINKEY,                       XK_s,      spawn,          {.v = spotify } },
	{ MODKEY|ControlMask,           XK_q,      spawn,          {.v = logout } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

