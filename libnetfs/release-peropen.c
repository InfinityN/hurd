/* 
   Copyright (C) 1996 Free Software Foundation, Inc.
   Written by Michael I. Bushnell, p/BSG.

   This file is part of the GNU Hurd.

   The GNU Hurd is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   The GNU Hurd is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA. */

#include "netfs.h"

void
netfs_release_peropen (struct peropen *po)
{
  mutex_lock (&po->np->lock);
  if (--po->refcnt)
    mutex_unlock (&po->np->lock);
  else
    {
      mach_port_deallocate (mach_task_self (), dotdotport);
      netfs_nput (po->np);
      free (po);
    }
}
