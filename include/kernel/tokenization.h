/******************************************************************************
 * 
 * @file tokenization.h
 * @date June 14, 2025
 * @author Diep-Thanh-Phuong
 * @copyright
 *  Copyright (c) 2025 Diep-Thanh-Phuong
 *  This file is part of CAS.
 * 
 *  CAS is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  CAS is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 *  License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with CAS. If not, see <https://www.gnu.org/licenses/>.
 * 
 *****************************************************************************/

#ifndef include_kernel_tokenization_h
#define include_kernel_tokenization_h

#include <kernel/token.h>

typedef void (*TokenHandler)(Token_t*, const char*, int*, int*);

extern void handle_stt(Token_t*, const char*, int*, int*);
extern void handle_num(Token_t*, const char*, int*, int*);
extern void handle_opr(Token_t*, const char*, int*, int*);
extern void handle_prt(Token_t*, const char*, int*, int*);
extern void handle_sym(Token_t*, const char*, int*, int*);

extern TokenHandler handler_tab[];

TOKENSTATE tokenize(Token_t *toks, const char *s, int *ntok);

#endif // include_kernel_tokenization_h