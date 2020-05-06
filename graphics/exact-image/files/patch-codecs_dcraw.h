--- codecs/dcraw.h.orig	2018-06-06 15:17:56 UTC
+++ codecs/dcraw.h
@@ -825,8 +825,9 @@ int CLASS ljpeg_start (struct jhead *jh, int info_only
   do {
     if (!fread (data, 2, 2, ifp)) return 0;
     tag =  data[0] << 8 | data[1];
-    len = (data[2] << 8 | data[3]) - 2;
-    if (tag <= 0xff00) return 0;
+    len = (data[2] << 8 | data[3]);
+    if (tag <= 0xff00 || len <= 2) return 0;
+    len -= 2;
     fread (data, 1, len, ifp);
     switch (tag) {
       case 0xffc3:
@@ -4438,22 +4439,22 @@ void CLASS vng_interpolate()
     -2,+0,+0,-1,0,0x06, -2,+0,+0,+0,1,0x02, -2,+0,+0,+1,0,0x03,
     -2,+1,-1,+0,0,0x04, -2,+1,+0,-1,1,0x04, -2,+1,+0,+0,0,0x06,
     -2,+1,+0,+1,0,0x02, -2,+2,+0,+0,1,0x04, -2,+2,+0,+1,0,0x04,
-    -1,-2,-1,+0,0,0x80, -1,-2,+0,-1,0,0x01, -1,-2,+1,-1,0,0x01,
-    -1,-2,+1,+0,1,0x01, -1,-1,-1,+1,0,0x88, -1,-1,+1,-2,0,0x40,
+    -1,-2,-1,+0,0,-128, -1,-2,+0,-1,0,0x01, -1,-2,+1,-1,0,0x01,
+    -1,-2,+1,+0,1,0x01, -1,-1,-1,+1,0,-120, -1,-1,+1,-2,0,0x40,
     -1,-1,+1,-1,0,0x22, -1,-1,+1,+0,0,0x33, -1,-1,+1,+1,1,0x11,
     -1,+0,-1,+2,0,0x08, -1,+0,+0,-1,0,0x44, -1,+0,+0,+1,0,0x11,
     -1,+0,+1,-2,1,0x40, -1,+0,+1,-1,0,0x66, -1,+0,+1,+0,1,0x22,
     -1,+0,+1,+1,0,0x33, -1,+0,+1,+2,1,0x10, -1,+1,+1,-1,1,0x44,
     -1,+1,+1,+0,0,0x66, -1,+1,+1,+1,0,0x22, -1,+1,+1,+2,0,0x10,
     -1,+2,+0,+1,0,0x04, -1,+2,+1,+0,1,0x04, -1,+2,+1,+1,0,0x04,
-    +0,-2,+0,+0,1,0x80, +0,-1,+0,+1,1,0x88, +0,-1,+1,-2,0,0x40,
+    +0,-2,+0,+0,1,-128, +0,-1,+0,+1,1,-120, +0,-1,+1,-2,0,0x40,
     +0,-1,+1,+0,0,0x11, +0,-1,+2,-2,0,0x40, +0,-1,+2,-1,0,0x20,
     +0,-1,+2,+0,0,0x30, +0,-1,+2,+1,1,0x10, +0,+0,+0,+2,1,0x08,
     +0,+0,+2,-2,1,0x40, +0,+0,+2,-1,0,0x60, +0,+0,+2,+0,1,0x20,
     +0,+0,+2,+1,0,0x30, +0,+0,+2,+2,1,0x10, +0,+1,+1,+0,0,0x44,
     +0,+1,+1,+2,0,0x10, +0,+1,+2,-1,1,0x40, +0,+1,+2,+0,0,0x60,
-    +0,+1,+2,+1,0,0x20, +0,+1,+2,+2,0,0x10, +1,-2,+1,+0,0,0x80,
-    +1,-1,+1,+1,0,0x88, +1,+0,+1,+2,0,0x08, +1,+0,+2,-1,0,0x40,
+    +0,+1,+2,+1,0,0x20, +0,+1,+2,+2,0,0x10, +1,-2,+1,+0,0,-128,
+    +1,-1,+1,+1,0,-120, +1,+0,+1,+2,0,0x08, +1,+0,+2,-1,0,0x40,
     +1,+0,+2,+1,0,0x10
   }, chood[] = { -1,-1, -1,0, -1,+1, 0,+1, +1,+1, +1,0, +1,-1, 0,-1 };
   ushort (*brow[5])[4], *pix;
@@ -8096,7 +8097,7 @@ void CLASS adobe_coeff (const char *make, const char *
 	{ 8035,435,-962,-6001,13872,2320,-1159,3065,5434 } },
     { "Photron BC2-HD", 0, 0,		/* DJC */
 	{ 14603,-4122,-528,-1810,9794,2017,-297,2763,5936 } },
-    { "Red One", 704, 0xffff,		/* DJC */
+    { "Red One", 704, -1,		/* DJC */
 	{ 21014,-7891,-2613,-3056,12201,856,-2203,5125,8042 } },
     { "Ricoh GR II", 0, 0,
 	{ 4630,-834,-423,-4977,12805,2417,-638,1467,6115 } },
@@ -9956,7 +9957,7 @@ void CLASS tiff_head (struct tiff_hdr *th, int full)
   strncpy (th->desc, desc, 512);
   strncpy (th->make, make, 64);
   strncpy (th->model, model, 64);
-  strcpy (th->soft, "dcraw v"DCRAW_VERSION);
+  strcpy (th->soft, "dcraw v" DCRAW_VERSION);
   t = localtime (&timestamp);
   sprintf (th->date, "%04d:%02d:%02d %02d:%02d:%02d",
       t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);