/*
** $Id: rect.c 13750 2011-03-15 06:41:03Z wanzheng $
**
** rect.c: Rectangle operations of GDI.
**
** Copyright (C) 2003 ~ 2007 Feynman Software.
** Copyright (C) 2001 ~ 2002 Wei Yongming.
**
** Current maintainer: Wei Yongming.
**
** Create date: 2000/06/12, derived from original gdi.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "gdi.h"

/**************************** Rectangle support ******************************/
BOOL GUIAPI IsRectEmpty (const RECT* prc)
{
    if( prc->left == prc->right ) return TRUE;
    if( prc->top == prc->bottom ) return TRUE;
    return FALSE;
}

BOOL GUIAPI EqualRect (const RECT* prc1, const RECT* prc2)
{
    if(prc1->left != prc2->left) return FALSE;
    if(prc1->top != prc2->top) return FALSE;
    if(prc1->right != prc2->right) return FALSE;
    if(prc1->bottom != prc2->bottom) return FALSE;

    return TRUE;
}

void GUIAPI NormalizeRect(RECT* pRect)
{
    int iTemp;

    if(pRect->left > pRect->right)
    {
         iTemp = pRect->left;
         pRect->left = pRect->right;
         pRect->right = iTemp;
    }

    if(pRect->top > pRect->bottom)
    {
         iTemp = pRect->top;
         pRect->top = pRect->bottom;
         pRect->bottom = iTemp;
    }
}

BOOL GUIAPI IsCovered(const RECT* prc1, const RECT* prc2)
{
    if (prc1->left < prc2->left
            || prc1->top < prc2->top
            || prc1->right > prc2->right
            || prc1->bottom > prc2->bottom)
        return FALSE;

    return TRUE;
}

BOOL GUIAPI IntersectRect(RECT* pdrc, const RECT* psrc1, const RECT* psrc2)
{
    pdrc->left = (psrc1->left > psrc2->left) ? psrc1->left : psrc2->left;
    pdrc->top  = (psrc1->top > psrc2->top) ? psrc1->top : psrc2->top;
    pdrc->right = (psrc1->right < psrc2->right) ? psrc1->right : psrc2->right;
    pdrc->bottom = (psrc1->bottom < psrc2->bottom) 
                   ? psrc1->bottom : psrc2->bottom;

    if(pdrc->left >= pdrc->right || pdrc->top >= pdrc->bottom)
        return FALSE;

    return TRUE;
}

BOOL GUIAPI DoesIntersect (const RECT* psrc1, const RECT* psrc2)
{
    int left, top, right, bottom;
    
    left = (psrc1->left > psrc2->left) ? psrc1->left : psrc2->left;
    top  = (psrc1->top > psrc2->top) ? psrc1->top : psrc2->top;
    right = (psrc1->right < psrc2->right) ? psrc1->right : psrc2->right;
    bottom = (psrc1->bottom < psrc2->bottom) 
                   ? psrc1->bottom : psrc2->bottom;

    if(left >= right || top >= bottom)
        return FALSE;

    return TRUE;
}

BOOL GUIAPI UnionRect(RECT* pdrc, const RECT* psrc1, const RECT* psrc2)
{
    RECT src1, src2;
    memcpy(&src1, psrc1, sizeof(RECT));
    memcpy(&src2, psrc2, sizeof(RECT));

    NormalizeRect(&src1);
    NormalizeRect(&src2);

    if (src1.left == src2.left 
        && src1.right == src2.right) {
        if (src1.top <= src2.top && src2.top <= src1.bottom) {
            pdrc->left = src1.left;
            pdrc->right = src1.right;
            pdrc->top = src1.top;
            pdrc->bottom = MAX(src1.bottom, src2.bottom);

            return TRUE;
        }
        else if (src1.top >= src2.top && src2.bottom >= src1.top) {
            pdrc->left = src1.left;
            pdrc->right = src1.right;
            pdrc->top = src2.top;
            pdrc->bottom = MAX(src1.bottom, src2.bottom);

            return TRUE;
       }

       return FALSE;
    }

    if (src1.top == src2.top 
        && src1.bottom == src2.bottom) {
        if (src1.left <= src2.left && src2.left <= src1.right) {
            pdrc->top = src1.top;
            pdrc->bottom = src1.bottom;
            pdrc->left = src1.left;
            pdrc->right = MAX(src1.right, src2.right);

            return TRUE;
        }
        else if (src1.left >= src2.left && src2.right >= src1.left) {
            pdrc->top = src1.top;
            pdrc->bottom = src1.bottom;
            pdrc->left = src2.left;
            pdrc->right = MAX(src1.right, src2.right);

            return TRUE;
       }

       return FALSE;
    }

    return FALSE;
}

void GUIAPI GetBoundRect (PRECT pdrc,  const RECT* psrc1, const RECT* psrc2)
{
    RECT src1, src2;
    memcpy(&src1, psrc1, sizeof(RECT));
    memcpy(&src2, psrc2, sizeof(RECT));

    NormalizeRect(&src1);
    NormalizeRect(&src2);

    if (IsRectEmpty(&src1)) {
        CopyRect(pdrc, &src2);
    }else if (IsRectEmpty(&src2)) {
        CopyRect(pdrc, &src1);
    }else{
        pdrc->left = (src1.left < src2.left) ? src1.left : src2.left;
        pdrc->top  = (src1.top < src2.top) ? src1.top : src2.top;
        pdrc->right = (src1.right > src2.right) ? src1.right : src2.right;
        pdrc->bottom = (src1.bottom > src2.bottom) 
            ? src1.bottom : src2.bottom;
    }
}

int GUIAPI SubtractRect(RECT* rc, const RECT* psrc1, const RECT* psrc2)
{
    RECT src, rcExpect, *prcExpect;
    int nCount = 0;
    
    src = *psrc1;
    rcExpect = *psrc2;
    prcExpect = &rcExpect;

    if (!DoesIntersect (&src, prcExpect)) {
        nCount = 1;
        rc[0] = src;
    }
    else {
        if(prcExpect->top > src.top)
        {
            rc[nCount].left  = src.left;
            rc[nCount].top   = src.top;
            rc[nCount].right = src.right;
            rc[nCount].bottom = prcExpect->top;
            nCount++;
            src.top = prcExpect->top;
        }
        if(prcExpect->bottom < src.bottom)
        {
            rc[nCount].top  = prcExpect->bottom;
            rc[nCount].left   = src.left;
            rc[nCount].right = src.right;
            rc[nCount].bottom = src.bottom;
            nCount++;
            src.bottom = prcExpect->bottom;
        }
        if(prcExpect->left > src.left)
        {
            rc[nCount].left  = src.left;
            rc[nCount].top   = src.top;
            rc[nCount].right = prcExpect->left;
            rc[nCount].bottom = src.bottom;
            nCount++;
        }
        if(prcExpect->right < src.right)
        {
            rc[nCount].left  = prcExpect->right;
            rc[nCount].top   = src.top;
            rc[nCount].right = src.right;
            rc[nCount].bottom = src.bottom;
            nCount++;
        }
    }

    return nCount;
}

