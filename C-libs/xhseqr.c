/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xhseqr.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 19-Jul-2022 14:47:38
 */

/* Include Files */
#include "xhseqr.h"
//#include "eig4x4cmplx_data.h"
#include "eigL4x4real_data.h"
//#include "eig4x4cmplx_rtwutil.h"
#include "eigL4x4real_rtwutil.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xdlapy3.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : creal_T h[16]
 *                creal_T z[16]
 * Return Type  : int
 */
int xhseqr(creal_T h[16], creal_T z[16])
{
  creal_T b_v[2];
  creal_T sc;
  creal_T v;
  double ba;
  double bb;
  double br;
  double im;
  double re;
  double s;
  double t_im;
  double t_re;
  double tst;
  double u_im;
  double u_re;
  int L;
  int b_i;
  int b_k;
  int c_k;
  int h_tmp;
  int i;
  int info;
  int its;
  int ix0;
  int j;
  int k;
  int knt;
  int m;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  boolean_T goto140;
  boolean_T goto70;
  info = 0;
  h[2].re = 0.0;
  h[2].im = 0.0;
  h[3].re = 0.0;
  h[3].im = 0.0;
  h[7].re = 0.0;
  h[7].im = 0.0;
  for (i = 0; i < 3; i++) {
    b_i = (i + (i << 2)) + 1;
    if (h[b_i].im != 0.0) {
      tst = h[b_i].re;
      t_im = h[b_i].im;
      br = fabs(h[b_i].re) + fabs(h[b_i].im);
      if (t_im == 0.0) {
        sc.re = tst / br;
        sc.im = 0.0;
      } else if (tst == 0.0) {
        sc.re = 0.0;
        sc.im = t_im / br;
      } else {
        sc.re = tst / br;
        sc.im = t_im / br;
      }
      br = rt_hypotd_snf(sc.re, sc.im);
      if (-sc.im == 0.0) {
        re = sc.re / br;
        im = 0.0;
      } else if (sc.re == 0.0) {
        re = 0.0;
        im = -sc.im / br;
      } else {
        re = sc.re / br;
        im = -sc.im / br;
      }
      h[b_i].re = rt_hypotd_snf(tst, h[b_i].im);
      h[b_i].im = 0.0;
      h_tmp = (i + 1) << 2;
      ix0 = (i + h_tmp) + 2;
      b_i = ix0 + ((2 - i) << 2);
      for (k = ix0; k <= b_i; k += 4) {
        t_im = re * h[k - 1].im + im * h[k - 1].re;
        h[k - 1].re = re * h[k - 1].re - im * h[k - 1].im;
        h[k - 1].im = t_im;
      }
      ix0 = h_tmp + 1;
      knt = i + 3;
      if (4 < knt) {
        knt = 4;
      }
      b_i = h_tmp + knt;
      for (k = ix0; k <= b_i; k++) {
        t_im = re * h[k - 1].im + -im * h[k - 1].re;
        h[k - 1].re = re * h[k - 1].re - -im * h[k - 1].im;
        h[k - 1].im = t_im;
      }
      b_i = h_tmp + 4;
      for (k = ix0; k <= b_i; k++) {
        t_im = re * z[k - 1].im + -im * z[k - 1].re;
        z[k - 1].re = re * z[k - 1].re - -im * z[k - 1].im;
        z[k - 1].im = t_im;
      }
    }
  }
  i = 3;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = -1;
    goto140 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && (k + 1 > L + 2)) {
        b_i = k + ((k - 1) << 2);
        t_im = fabs(h[b_i].re);
        ba = t_im + fabs(h[b_i].im);
        if (ba <= 4.0083367200179456E-292) {
          exitg3 = true;
        } else {
          knt = k + (k << 2);
          bb = fabs(h[knt].re) + fabs(h[knt].im);
          tst = (fabs(h[b_i - 1].re) + fabs(h[b_i - 1].im)) + bb;
          if (tst == 0.0) {
            if (k - 1 >= 1) {
              tst = fabs(h[(k + ((k - 2) << 2)) - 1].re);
            }
            if (k + 2 <= 4) {
              tst += fabs(h[knt + 1].re);
            }
          }
          if (t_im <= 2.2204460492503131E-16 * tst) {
            t_im = fabs(h[knt - 1].re) + fabs(h[knt - 1].im);
            if (ba > t_im) {
              tst = ba;
              ba = t_im;
            } else {
              tst = t_im;
            }
            t_im = fabs(h[b_i - 1].re - h[knt].re) +
                   fabs(h[b_i - 1].im - h[knt].im);
            if (bb > t_im) {
              t_re = bb;
              bb = t_im;
            } else {
              t_re = t_im;
            }
            s = t_re + tst;
            if (ba * (tst / s) <=
                fmax(4.0083367200179456E-292,
                     2.2204460492503131E-16 * (bb * (t_re / s)))) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }
      L = k - 1;
      if (k + 1 > 1) {
        b_i = k + ((k - 1) << 2);
        h[b_i].re = 0.0;
        h[b_i].im = 0.0;
      }
      if (k + 1 >= i + 1) {
        goto140 = true;
        exitg2 = true;
      } else {
        if (its == 10) {
          ix0 = k + (k << 2);
          t_re = 0.75 * fabs(h[(k + (k << 2)) + 1].re) + h[ix0].re;
          t_im = h[ix0].im;
        } else if (its == 20) {
          ix0 = i + (i << 2);
          t_re = 0.75 * fabs(h[i + ((i - 1) << 2)].re) + h[ix0].re;
          t_im = h[ix0].im;
        } else {
          ix0 = i + (i << 2);
          t_re = h[ix0].re;
          t_im = h[ix0].im;
          v = h[ix0 - 1];
          b_sqrt(&v);
          knt = i + ((i - 1) << 2);
          sc = h[knt];
          b_sqrt(&sc);
          u_re = v.re * sc.re - v.im * sc.im;
          u_im = v.re * sc.im + v.im * sc.re;
          s = fabs(u_re) + fabs(u_im);
          if (s != 0.0) {
            bb = 0.5 * (h[knt - 1].re - h[ix0].re);
            im = 0.5 * (h[knt - 1].im - h[ix0].im);
            ba = fabs(bb) + fabs(im);
            s = fmax(s, ba);
            if (im == 0.0) {
              t_re = bb / s;
              t_im = 0.0;
            } else if (bb == 0.0) {
              t_re = 0.0;
              t_im = im / s;
            } else {
              t_re = bb / s;
              t_im = im / s;
            }
            re = t_re * t_re - t_im * t_im;
            tst = t_re * t_im;
            if (u_im == 0.0) {
              sc.re = u_re / s;
              sc.im = 0.0;
            } else if (u_re == 0.0) {
              sc.re = 0.0;
              sc.im = u_im / s;
            } else {
              sc.re = u_re / s;
              sc.im = u_im / s;
            }
            t_im = sc.re * sc.re - sc.im * sc.im;
            t_re = sc.re * sc.im;
            v.re = re + t_im;
            v.im = (tst + tst) + (t_re + t_re);
            b_sqrt(&v);
            sc.re = s * v.re;
            sc.im = s * v.im;
            if (ba > 0.0) {
              if (im == 0.0) {
                t_re = bb / ba;
                t_im = 0.0;
              } else if (bb == 0.0) {
                t_re = 0.0;
                t_im = im / ba;
              } else {
                t_re = bb / ba;
                t_im = im / ba;
              }
              if (t_re * sc.re + t_im * sc.im < 0.0) {
                sc.re = -sc.re;
                sc.im = -sc.im;
              }
            }
            br = bb + sc.re;
            t_re = im + sc.im;
            if (t_re == 0.0) {
              if (u_im == 0.0) {
                bb = u_re / br;
                tst = 0.0;
              } else if (u_re == 0.0) {
                bb = 0.0;
                tst = u_im / br;
              } else {
                bb = u_re / br;
                tst = u_im / br;
              }
            } else if (br == 0.0) {
              if (u_re == 0.0) {
                bb = u_im / t_re;
                tst = 0.0;
              } else if (u_im == 0.0) {
                bb = 0.0;
                tst = -(u_re / t_re);
              } else {
                bb = u_im / t_re;
                tst = -(u_re / t_re);
              }
            } else {
              ba = fabs(br);
              tst = fabs(t_re);
              if (ba > tst) {
                s = t_re / br;
                tst = br + s * t_re;
                bb = (u_re + s * u_im) / tst;
                tst = (u_im - s * u_re) / tst;
              } else if (tst == ba) {
                if (br > 0.0) {
                  t_im = 0.5;
                } else {
                  t_im = -0.5;
                }
                if (t_re > 0.0) {
                  tst = 0.5;
                } else {
                  tst = -0.5;
                }
                bb = (u_re * t_im + u_im * tst) / ba;
                tst = (u_im * t_im - u_re * tst) / ba;
              } else {
                s = br / t_re;
                tst = t_re + s * br;
                bb = (s * u_re + u_im) / tst;
                tst = (s * u_im - u_re) / tst;
              }
            }
            t_re = h[ix0].re - (u_re * bb - u_im * tst);
            t_im = h[ix0].im - (u_re * tst + u_im * bb);
          }
        }
        goto70 = false;
        m = i;
        exitg3 = false;
        while ((!exitg3) && (m > k + 1)) {
          knt = m + ((m - 1) << 2);
          sc.re = h[knt - 1].re - t_re;
          sc.im = h[knt - 1].im - t_im;
          tst = h[knt].re;
          s = (fabs(sc.re) + fabs(sc.im)) + fabs(tst);
          if (sc.im == 0.0) {
            re = sc.re / s;
            im = 0.0;
          } else if (sc.re == 0.0) {
            re = 0.0;
            im = sc.im / s;
          } else {
            re = sc.re / s;
            im = sc.im / s;
          }
          sc.re = re;
          sc.im = im;
          tst /= s;
          b_v[0] = sc;
          b_v[1].re = tst;
          b_v[1].im = 0.0;
          b_i = m + (m << 2);
          if (fabs(h[(m + ((m - 2) << 2)) - 1].re) * fabs(tst) <=
              2.2204460492503131E-16 *
                  ((fabs(re) + fabs(im)) *
                   ((fabs(h[knt - 1].re) + fabs(h[knt - 1].im)) +
                    (fabs(h[b_i].re) + fabs(h[b_i].im))))) {
            goto70 = true;
            exitg3 = true;
          } else {
            m--;
          }
        }
        if (!goto70) {
          knt = k + (k << 2);
          sc.re = h[knt].re - t_re;
          sc.im = h[knt].im - t_im;
          tst = h[(k + (k << 2)) + 1].re;
          s = (fabs(sc.re) + fabs(sc.im)) + fabs(tst);
          if (sc.im == 0.0) {
            b_v[0].re = sc.re / s;
            b_v[0].im = 0.0;
          } else if (sc.re == 0.0) {
            b_v[0].re = 0.0;
            b_v[0].im = sc.im / s;
          } else {
            b_v[0].re = sc.re / s;
            b_v[0].im = sc.im / s;
          }
          tst /= s;
          b_v[1].re = tst;
          b_v[1].im = 0.0;
        }
        for (b_k = m; b_k <= i; b_k++) {
          if (b_k > m) {
            knt = b_k + ((b_k - 2) << 2);
            b_v[0] = h[knt - 1];
            b_v[1] = h[knt];
          }
          sc = b_v[0];
          bb = b_v[1].re;
          im = b_v[1].im;
          t_re = 0.0;
          t_im = 0.0;
          tst = rt_hypotd_snf(b_v[1].re, b_v[1].im);
          if ((tst != 0.0) || (b_v[0].im != 0.0)) {
            tst = xdlapy3(b_v[0].re, b_v[0].im, tst);
            if (b_v[0].re >= 0.0) {
              tst = -tst;
            }
            if (fabs(tst) < 1.0020841800044864E-292) {
              knt = -1;
              do {
                knt++;
                bb *= 9.9792015476736E+291;
                im *= 9.9792015476736E+291;
                tst *= 9.9792015476736E+291;
                sc.re *= 9.9792015476736E+291;
                sc.im *= 9.9792015476736E+291;
              } while (!(fabs(tst) >= 1.0020841800044864E-292));
              tst = xdlapy3(sc.re, sc.im, rt_hypotd_snf(bb, im));
              if (sc.re >= 0.0) {
                tst = -tst;
              }
              t_im = tst - sc.re;
              if (0.0 - sc.im == 0.0) {
                t_re = t_im / tst;
                t_im = 0.0;
              } else if (t_im == 0.0) {
                t_re = 0.0;
                t_im = (0.0 - sc.im) / tst;
              } else {
                t_re = t_im / tst;
                t_im = (0.0 - sc.im) / tst;
              }
              v.re = sc.re - tst;
              v.im = sc.im;
              sc = recip(v);
              re = sc.re * bb - sc.im * im;
              im = sc.re * im + sc.im * bb;
              bb = re;
              for (c_k = 0; c_k <= knt; c_k++) {
                tst *= 1.0020841800044864E-292;
              }
              sc.re = tst;
              sc.im = 0.0;
            } else {
              t_im = tst - b_v[0].re;
              if (0.0 - b_v[0].im == 0.0) {
                t_re = t_im / tst;
                t_im = 0.0;
              } else if (t_im == 0.0) {
                t_re = 0.0;
                t_im = (0.0 - b_v[0].im) / tst;
              } else {
                t_re = t_im / tst;
                t_im = (0.0 - b_v[0].im) / tst;
              }
              v.re = b_v[0].re - tst;
              v.im = b_v[0].im;
              v = recip(v);
              bb = v.re * b_v[1].re - v.im * b_v[1].im;
              im = v.re * b_v[1].im + v.im * b_v[1].re;
              sc.re = tst;
              sc.im = 0.0;
            }
          }
          b_v[0] = sc;
          b_v[1].re = bb;
          b_v[1].im = im;
          if (b_k > m) {
            h[(b_k + ((b_k - 2) << 2)) - 1] = sc;
            b_i = b_k + ((b_k - 2) << 2);
            h[b_i].re = 0.0;
            h[b_i].im = 0.0;
          }
          tst = t_re * bb - t_im * im;
          for (j = b_k; j < 5; j++) {
            ix0 = b_k + ((j - 1) << 2);
            sc.re = (t_re * h[ix0 - 1].re - -t_im * h[ix0 - 1].im) +
                    tst * h[ix0].re;
            sc.im = (t_re * h[ix0 - 1].im + -t_im * h[ix0 - 1].re) +
                    tst * h[ix0].im;
            h[ix0 - 1].re -= sc.re;
            h[ix0 - 1].im -= sc.im;
            h[ix0].re -= sc.re * bb - sc.im * im;
            h[ix0].im -= sc.re * im + sc.im * bb;
          }
          if (b_k + 2 < i + 1) {
            b_i = b_k + 1;
          } else {
            b_i = i;
          }
          for (j = 0; j <= b_i; j++) {
            ix0 = j + ((b_k - 1) << 2);
            knt = j + (b_k << 2);
            sc.re = (t_re * h[ix0].re - t_im * h[ix0].im) + tst * h[knt].re;
            sc.im = (t_re * h[ix0].im + t_im * h[ix0].re) + tst * h[knt].im;
            h[ix0].re -= sc.re;
            h[ix0].im -= sc.im;
            h[knt].re -= sc.re * bb - sc.im * -im;
            h[knt].im -= sc.re * -im + sc.im * bb;
          }
          ix0 = (b_k - 1) << 2;
          knt = b_k << 2;
          sc.re = (t_re * z[ix0].re - t_im * z[ix0].im) + tst * z[knt].re;
          sc.im = (t_re * z[ix0].im + t_im * z[ix0].re) + tst * z[knt].im;
          z[ix0].re -= sc.re;
          z[ix0].im -= sc.im;
          z[knt].re -= sc.re * bb - sc.im * -im;
          z[knt].im -= sc.re * -im + sc.im * bb;
          sc.re = (t_re * z[ix0 + 1].re - t_im * z[ix0 + 1].im) +
                  tst * z[knt + 1].re;
          sc.im = (t_re * z[ix0 + 1].im + t_im * z[ix0 + 1].re) +
                  tst * z[knt + 1].im;
          z[ix0 + 1].re -= sc.re;
          z[ix0 + 1].im -= sc.im;
          z[knt + 1].re -= sc.re * bb - sc.im * -im;
          z[knt + 1].im -= sc.re * -im + sc.im * bb;
          sc.re = (t_re * z[ix0 + 2].re - t_im * z[ix0 + 2].im) +
                  tst * z[knt + 2].re;
          sc.im = (t_re * z[ix0 + 2].im + t_im * z[ix0 + 2].re) +
                  tst * z[knt + 2].im;
          z[ix0 + 2].re -= sc.re;
          z[ix0 + 2].im -= sc.im;
          z[knt + 2].re -= sc.re * bb - sc.im * -im;
          z[knt + 2].im -= sc.re * -im + sc.im * bb;
          sc.re = (t_re * z[ix0 + 3].re - t_im * z[ix0 + 3].im) +
                  tst * z[knt + 3].re;
          sc.im = (t_re * z[ix0 + 3].im + t_im * z[ix0 + 3].re) +
                  tst * z[knt + 3].im;
          z[ix0 + 3].re -= sc.re;
          z[ix0 + 3].im -= sc.im;
          z[knt + 3].re -= sc.re * bb - sc.im * -im;
          z[knt + 3].im -= sc.re * -im + sc.im * bb;
          if ((b_k == m) && (m > k + 1)) {
            br = rt_hypotd_snf(1.0 - t_re, 0.0 - t_im);
            if (0.0 - t_im == 0.0) {
              re = (1.0 - t_re) / br;
              im = 0.0;
            } else if (1.0 - t_re == 0.0) {
              re = 0.0;
              im = (0.0 - t_im) / br;
            } else {
              re = (1.0 - t_re) / br;
              im = (0.0 - t_im) / br;
            }
            knt = m + ((m - 1) << 2);
            t_im = h[knt].re * -im + h[knt].im * re;
            h[knt].re = h[knt].re * re - h[knt].im * -im;
            h[knt].im = t_im;
            if (m + 2 <= i + 1) {
              knt = (m << 2) + 3;
              t_im = h[knt].re * im + h[knt].im * re;
              h[knt].re = h[knt].re * re - h[knt].im * im;
              h[knt].im = t_im;
            }
            for (j = m; j <= i + 1; j++) {
              if (j != m + 1) {
                if (4 > j) {
                  ix0 = j + (j << 2);
                  b_i = ix0 + ((3 - j) << 2);
                  for (c_k = ix0; c_k <= b_i; c_k += 4) {
                    t_im = re * h[c_k - 1].im + im * h[c_k - 1].re;
                    h[c_k - 1].re = re * h[c_k - 1].re - im * h[c_k - 1].im;
                    h[c_k - 1].im = t_im;
                  }
                }
                knt = (j - 1) << 2;
                h_tmp = knt + 1;
                b_i = (knt + j) - 1;
                for (c_k = h_tmp; c_k <= b_i; c_k++) {
                  t_im = re * h[c_k - 1].im + -im * h[c_k - 1].re;
                  h[c_k - 1].re = re * h[c_k - 1].re - -im * h[c_k - 1].im;
                  h[c_k - 1].im = t_im;
                }
                b_i = knt + 4;
                for (c_k = h_tmp; c_k <= b_i; c_k++) {
                  t_im = re * z[c_k - 1].im + -im * z[c_k - 1].re;
                  z[c_k - 1].re = re * z[c_k - 1].re - -im * z[c_k - 1].im;
                  z[c_k - 1].im = t_im;
                }
              }
            }
          }
        }
        knt = i + ((i - 1) << 2);
        sc = h[knt];
        if (h[knt].im != 0.0) {
          t_im = rt_hypotd_snf(h[knt].re, h[knt].im);
          h[knt].re = t_im;
          h[knt].im = 0.0;
          if (sc.im == 0.0) {
            re = sc.re / t_im;
            im = 0.0;
          } else if (sc.re == 0.0) {
            re = 0.0;
            im = sc.im / t_im;
          } else {
            re = sc.re / t_im;
            im = sc.im / t_im;
          }
          if (4 > i + 1) {
            ix0 = (i + ((i + 1) << 2)) + 1;
            b_i = ix0 + ((2 - i) << 2);
            for (k = ix0; k <= b_i; k += 4) {
              t_im = re * h[k - 1].im + -im * h[k - 1].re;
              h[k - 1].re = re * h[k - 1].re - -im * h[k - 1].im;
              h[k - 1].im = t_im;
            }
          }
          knt = i << 2;
          h_tmp = knt + 1;
          b_i = knt + i;
          for (k = h_tmp; k <= b_i; k++) {
            t_im = re * h[k - 1].im + im * h[k - 1].re;
            h[k - 1].re = re * h[k - 1].re - im * h[k - 1].im;
            h[k - 1].im = t_im;
          }
          b_i = knt + 4;
          for (k = h_tmp; k <= b_i; k++) {
            t_im = re * z[k - 1].im + im * z[k - 1].re;
            z[k - 1].re = re * z[k - 1].re - im * z[k - 1].im;
            z[k - 1].im = t_im;
          }
        }
        its++;
      }
    }
    if (!goto140) {
      info = i + 1;
      exitg1 = true;
    } else {
      i = L;
    }
  }
  h[3].re = 0.0;
  h[3].im = 0.0;
  return info;
}

/*
 * File trailer for xhseqr.c
 *
 * [EOF]
 */
