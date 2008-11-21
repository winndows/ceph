// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 * 
 */

#ifndef __MPGSTATS_H
#define __MPGSTATS_H

#include "osd/osd_types.h"

class MPGStats : public Message {
public:
  ceph_fsid fsid;
  map<pg_t,pg_stat_t> pg_stat;
  osd_stat_t osd_stat;
  epoch_t epoch;
  utime_t had_map_for;
  
  MPGStats() : Message(MSG_PGSTATS) {}
  MPGStats(ceph_fsid& f, epoch_t e, utime_t had) : 
    Message(MSG_PGSTATS), fsid(f), epoch(e), had_map_for(had) {}

  const char *get_type_name() { return "pg_stats"; }
  void print(ostream& out) {
    out << "pg_stats";
  }

  void encode_payload() {
    ::encode(fsid, payload);
    ::encode(osd_stat, payload);
    ::encode(pg_stat, payload);
    ::encode(epoch, payload);
    ::encode(had_map_for, payload);
  }
  void decode_payload() {
    bufferlist::iterator p = payload.begin();
    ::decode(fsid, p);
    ::decode(osd_stat, p);
    ::decode(pg_stat, p);
    ::decode(epoch, p);
    ::decode(had_map_for, p);
  }
};

#endif
