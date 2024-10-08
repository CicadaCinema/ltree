#define NAME 		"3D IFS"
#define RND 		( ( float ) rand ( ) / RAND_MAX )
#define RNDBOOL	( 0 == int ( RND * 2 ) )
#define	RNDSGN	( SGN ( 0.5f + RND ) )

// Z buffer depth:
#define ZDEPTH	16384

// Palette size:
#define PALSIZE	8192	// *** Allways 2 ^ int ( |n| ) ***

// Screen, pixel & Z-buffer sizes:
#define WIDTH		( 800 )
#define HEIGHT	( 600 )
#define MIDX		( WIDTH>>1 )
#define MIDY		( HEIGHT>>1 )
#define BWIDTH	( WIDTH<<1 )
#define BHEIGHT	( HEIGHT<<1 )
#define BMIDX		( MIDX<<1 )
#define BMIDY		( MIDY<<1 )
#define LWIDTH	( 4096 )
#define LHEIGHT	( 4096 )
#define LMIDX		( LWIDTH>>1 )
#define LMIDY		( LHEIGHT>>1 )

//// IFS! IFS!! IFS!!! ////
#define ANTAL		8

// Palette displaymodes:
#define SERP		( 1 )
#define ABSZ		( 2 )
#define HOTB		( 3 )

// Coloursation modes:
#define	NORMALCOLOURS	( 0 )
#define FUNKYCOLOURS	( 1 )

// Fonts:
#define SMALLFONT		( 0 )
#define MEDIUMFONT	( 1 )
#define BIGFONT			( 2 )

// Selectable axioms:
#define	USELOGS 		( 0 )
#define	USECUBES 		( 1 )
#define	USESPHEARS 	( 2 )

// Error codes:
#define	WASNOERROR	( 0 )
#define	WASERROR 		( 1 )

// CODE MAKRONS:

// Draw a filled box:
#define FILLBOX(xstart, ystart, xend, yend, fillcol)\
				(	lixs = xstart,\
        	liys = ystart,\
          lixe = xend,\
          liye = yend,\
          lcol = fillcol,\
          drawBoxi ( )\
        )
// Draw a filled box.

// Outlined textbox: (outline is one point wider than the coordinates)
#define TEXTBOX(xstart, ystart, xend, yend, bordercol, fillcol)\
				(	FILLBOX ( xstart - 1, ystart - 1, xend + 1, yend + 1, bordercol ),\
          FILLBOX ( xstart, ystart, xend, yend, fillcol )\
        )
// Outlined textbox.

// Color cycler:
#define COLPAL\
				{	tcolor = lpCols [ pali ];\
				  tRed = ( tcolor >> 16 ) & 0xFF;\
				  tGreen = ( tcolor >> 8 ) & 0xFF;\
				  tBlue = tcolor & 0xFF;\
				  dcr = ( ( dcr + tRed) >> 1 ) & 0xFF;\
				  dcg = ( ( dcg + tGreen) >> 1 ) & 0xFF;\
				  dcb = ( ( dcb + tBlue) >> 1 ) & 0xFF;\
        }
// Color cycler.

// Color selector:
#define COLMOD\
				{	dcr = ( ( dcr + tcr [ coli ] ) >> 1 ) & 0xFF;\
					dcg = ( ( dcg + tcg [ coli ] ) >> 1 ) & 0xFF;\
					dcb = ( ( dcb + tcb [ coli ] ) >> 1 ) & 0xFF;\
        }
// Color selector.

// Branch structure:
struct DTBRA	{
                long double  scale;
                long double  height;
                long double  leanc;
                long double  leans;
                long double  rotatec;
                long double  rotates;
                long double  twistc;
                long double  twists;
							};
// Tree structure:
struct DTIFS	{
								char 	 			name [ 16 ];
                int					branches;
                bool				usehig;
                bool				glblscl;
                bool				sctrnsl;
                bool				usetwst;
                long double	radius;
                long double height;
                DTBRA		stem;
                DTBRA		branch_1;
                DTBRA		branch_2;
                DTBRA		branch_3;
                DTBRA		branch_4;
                DTBRA		branch_5;
                DTBRA		branch_6;
                DTBRA		branch_7;
							};

