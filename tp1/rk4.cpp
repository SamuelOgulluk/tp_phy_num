void rk4(int n, double x,double y[] ,double dx,
               void deriv(int, double, double[], double[]))
/*-----------------------------------------
 sous programme de resolution d'equations
 differentielles du premier ordre par
 la methode de Runge-Kutta d'ordre 4
 x = abscisse
 y = valeurs des fonctions
 dx = pas
 n = nombre d'equations differentielles
 deriv = variable contenant le nom du
 sous-programme qui calcule les derivees
 ----------------------------------------*/
{
int i ;
double ddx ;
/* d1, d2, d3, d4 = estimations des derivees
   yp = estimations intermediaires des fonctions */
double d1[n], d2[n], d3[n], d4[n], yp[n];

ddx = dx/2;                /* demi-pas */

deriv(n,x,y,d1) ;          /* 1ere estimation */          

for( i = 0; i< n; i++){ yp[i] = y[i] + d1[i]*ddx ; }
deriv(n,x+ddx,yp,d2) ;     /* 2eme estimat. (1/2 pas) */

for( i = 0; i < n; i++){ yp[i] = y[i] + d2[i]*ddx ; }
deriv(n,x+ddx,yp,d3) ; /* 3eme estimat. (1/2 pas) */

for( i = 0; i< n; i++){ yp[i] = y[i] + d3[i]*dx ;}
deriv(n,x+dx,yp,d4) ;      /* 4eme estimat. (1 pas) */
/* estimation de y pour le pas suivant en utilisant
  une moyenne pondérée des dérivées en remarquant
  que : 1/6 + 1/3 + 1/3 + 1/6 = 1 */

for( i = 0; i < n ; i++)
 { y[i] = y[i] + dx*( d1[i] + 2*d2[i] + 2*d3[i] + d4[i] )/6 ; }
}
