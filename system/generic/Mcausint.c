/* Causal integration on the first axis. */
/*
  Copyright (C) 2004 University of Texas at Austin

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <rsf.h>

int main(int argc, char* argv[])
{
    int n1, n2, i2;
    bool adj;
    float *pp, *qq;
    sf_file in=NULL, out=NULL;

    sf_init(argc,argv);

    in = sf_input("in");
    out = sf_output("out");

    if (!sf_histint(in,"n1",&n1)) sf_error("No n1= in input");
    n2 = sf_leftsize(in,1);

    pp = sf_floatalloc(n1);
    qq = sf_floatalloc(n1);

    if (!sf_getbool("adj",&adj)) adj=false;
    /* if y, do adjoint integration */

    for (i2=0; i2 < n2; i2++) {
	sf_floatread(pp,n1,in);
	if (adj) {
	    sf_causint_lop (true,false,n1,n1,qq,pp);
	} else {
	    sf_causint_lop (false,false,n1,n1,pp,qq);
	}
	sf_floatwrite(qq,n1,out);
    }


    exit(0);
}
