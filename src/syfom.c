/*
 * Title:	sysfom.c - Display figures-of-merit
 * Author:	T.E.Dickey
 * Created:	27 Oct 83
 * Last update:	27 Oct 83
 *
 * Function:	Obtain a character string from the operating system which
 *		shows both elapsed and actual CPU times.  Return this string
 *		to the user for inclusion in the process-listing.
 *
 * Parameters:	co_	=> caller's output buffer.  If null pointer, initialize
 *			   timer-control-block.
 */

static	char	bfr[256];
static	char	*handle_ = 0;
static	int	code	= 0;

sysfom_x (dx_)
struct {
	short len;
	short typ;
	char  *c_;
	} *dx_;
{
int	len	= dx_->len;
char	*c_	= dx_->c_;

	strncpy (bfr, dx_->c_, len);
	bfr[len] = '\0';
}

/*
 * Main procedure:
 */

sysfom (co_)
char	*co_;
{
	if ((co_ == 0) || (handle_ == 0))
		lib$init_timer(&handle_);
	if (co_)
	{
		lib$show_timer (&handle_, &code, sysfom_x);
		strcpy (co_, &bfr[1]);
	}
}
