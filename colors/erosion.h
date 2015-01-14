#define base03 "#504339"  //normbordercolor
#define base1  "#9a875f"  //selbordercolor

#define base02 "#181512"  //normbgcolor
#define base01 "#556D70"  //normfgcolor

#define base2  "#181512"  //selbgcolor
#define base3  "#9a875f"  //selfgcolor

static const char *colorname[] = {
	/* 8 normal colors */
	"black",
	"red3",
	"green3",
	"yellow3",
	"blue2",
	"magenta3",
	"cyan3",
	"gray90",

	/* 8 bright colors */
	"gray50",
	"red",
	"green",
	"yellow",
	"#5c5cff",
	"magenta",
	"cyan",
	"white",

	[255] = 0,

	/* more colors can be added after 255 to use with DefaultXX */
	"#cccccc",
};

static unsigned int defaultfg = 7;
static unsigned int defaultbg = 0;
static unsigned int defaultcs = 256;
