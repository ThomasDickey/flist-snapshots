  	/* Copyright 1984 (C) Thomas E. Dickey */

/*
 * Title:	freelist.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	28 May 1984
 * Last update:	28 May 1984
 *
 * Function:	This procedure releases all elements in a linked list which
 *		were previously allocated using malloc, or calloc.  The
 *		list is linked with the next-pointer in the first location
 *		of each entry.  (The storage allocator knows how long the
 *		entries actually were.)
 */

typedef	struct	{
	struct	ENTRY	*next;
	}	ENTRY;

freelist (first_)
ENTRY	*first_;
{
ENTRY	*next_;

	while (first_)
	{
		next_ = first_->next;
		cfree (first_);
		first_ = next_;
	}
}
