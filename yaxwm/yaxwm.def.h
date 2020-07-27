/* In order to customize settings or add new commands
 * copy this file to yaxwm.h and edit it
 *
 * see license file for copyright and license details */


static unsigned int border[] = {
	[BORD_WIDTH]     = 1,          /* total border width in pixels */
	[BORD_FOCUS]     = 0xFF6699cc, /* focused window border colour (inner) */
	[BORD_URGENT]    = 0xFFee5555, /* urgent window border colour (inner) */
	[BORD_UNFOCUS]   = 0xFF444444, /* unfocused window border colour (inner) */
	[BORD_O_WIDTH]   = 0,          /* outer border width in pixels */
	[BORD_O_FOCUS]   = 0xFF222222, /* focused window border colour (outer) */
	[BORD_O_URGENT]  = 0xFF222222, /* urgent window border colour (outer) */
	[BORD_O_UNFOCUS] = 0xFF222222, /* unfocused window border colour (outer) */
};

static int globalcfg[] = {
	[GLB_SMART_GAP]    = 1,  /* disable gaps in layouts with only one visible window */
	[GLB_SMART_BORDER] = 1,  /* disable borders in layouts with only one visible window */
	[GLB_SIZEHINT]     = 0,  /* respect size hints in tiled layouts */
	[GLB_FOCUS_MOUSE]  = 1,  /* enable focus follows mouse */
	[GLB_FOCUS_URGENT] = 1,  /* enable focus urgent windows */
	[GLB_TILETOHEAD]   = 0,  /* place new clients at the tail of the stack */
	[GLB_NUMWS]        = 0,  /* number of workspaces currently allocated */
	[GLB_MIN_XY]       = 10, /* minimum window area allowed inside the screen when moving */
	[GLB_MIN_WH]       = 50, /* minimum window size allowed when resizing */
};

static const char *cursors[] = {
	/* see: https://tronche.com/gui/x/xlib/appendix/b/ */
	[CURS_MOVE]   = "fleur",
	[CURS_NORMAL] = "arrow",
	[CURS_RESIZE] = "sizing",
};

/* default modifier and buttons for mouse move/resize */
static xcb_mod_mask_t mousemod = XCB_MOD_MASK_4;
static xcb_button_t mousemove = XCB_BUTTON_INDEX_1;
static xcb_button_t mouseresize = XCB_BUTTON_INDEX_3;

static void albumart(Client *c, int closed)
{ /* example of a simple callback for album art windows */
	switch (closed) {
	case 0: /* opened */
		c->ws->padr = c->w + (2 * c->ws->gappx);
		gravitate(c, GRAV_RIGHT, GRAV_CENTER, 1);
		focus(c->snext);
		break;
	case 1: /* closed */
		c->ws->padr = 0; break;
	}
}

/* "callback" names recognized for use with rules.
 * Callback functions have the following prototype: void function(Client *, int); */
static Callback callbacks[] = {
	/* name passed by user,    function name*/
	{ "albumart",                     albumart },
};

/* "layout" names used by cmdlayout() to parse arguments.
 * Layout functions have the following prototype: int function(Workspace *); */
static Layout layouts[] = {
	{ "tile",    tile    }, /* first is default */
	{ "mono",    mono    },
	{ "grid",    grid    },
	{ "spiral",  spiral  },
	{ "dwindle", dwindle },
	{ "none",    NULL    },
};

static Workspace wsdef = { /* settings for newly created workspaces */
	1,           /* nmaster */
	3,           /* nstack  */
	0,           /* gappx   */
	0,           /* padl    */
	0,           /* padr    */
	0,           /* padt    */
	0,           /* padb    */
	0.55,        /* msplit  */
	0.55,        /* ssplit  */
	&layouts[0], /* layout  */

	/* unused values - inherited from Workspace struct */
	0, 0, { 0 }, NULL, NULL, NULL, NULL, NULL, NULL
};

/* primary keywords and parser functions
 * Keyword functions have the following prototype: void function(char **); */
static const Keyword keywords[] = {
	{ "mon",   cmdmon   },
	{ "rule",  cmdrule  },
	{ "set",   cmdset   },
	{ "win",   cmdwin   },
	{ "wm",    cmdwm    },
	{ "ws",    cmdws    },
	{ "print", cmdprint },
};

/* "set" keyword options, used by cmdset() to parse arguments
 * Keyword functions have the following prototype: void function(char **); */
static const Keyword setcmds[] = {
	{ "border", cmdborder  },
	{ "gap",    cmdgappx   },
	{ "layout", cmdlayout  },
	{ "master", cmdnmaster },
	{ "mouse",  cmdmouse   },
	{ "pad",    cmdpad     },
	{ "msplit", cmdmsplit   },
	{ "ssplit", cmdssplit  },
	{ "stack",  cmdnstack  },
};

/* "win" keyword options, used by cmdwin() to parse arguments
 * Keyword functions have the following prototype: void function(char **); */
static const Keyword wincmds[] = {
	{ "cycle",    cmdcycle    },
	{ "fakefull", cmdfakefull },
	{ "float",    cmdfloat    },
	{ "full",     cmdfull     },
	{ "focus",    cmdfocus    },
	{ "kill",     cmdkill     },
	{ "resize",   cmdresize   },
	{ "stick",    cmdstick    },
	{ "swap",     cmdswap     },
};

/* "ws" and "mon" commands used by cmdws() and cmdmon() to parse arguments.
 * Command functions have the following prototype: void function(int); */
static const Command wsmoncmds[] = {
	{ "follow", cmdfollow },
	{ "send",   cmdsend   },
	{ "view",   cmdview   },
};

