/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include "show_syncedimage_impl.h"
#include "showpngpicture.h"
#include <gnuradio/io_signature.h>

#define tolerance 10

namespace gr {
  namespace display {

    show_syncedimage::sptr
    show_syncedimage::make(const std::string &title,int imagewidth,int imageheight,QWidget *parent)
    {
      return gnuradio::get_initial_sptr (new show_syncedimage_impl(title,imagewidth, imageheight,parent));
    }

    /*
     * The private constructor
     */
    show_syncedimage_impl::show_syncedimage_impl(const std::string &title,int imagewidth,int imageheight,QWidget *parent)
      : gr::sync_block ("show_image",
                       gr::io_signature::make(1, 1, sizeof (float)),
                       gr::io_signature::make(0, 0, 0)),
                       d_title(title),d_width(imagewidth),d_height(imageheight),d_parent(parent) {
         d_main_gui = NULL;
         if(qApp != NULL) {
             d_qApplication = qApp;
         }
         else {
          int argc=1;
          char *argv =new char;
          argv[0] = '\0';
          d_qApplication = new QApplication(argc, &argv);
         }
         d_main_gui = new ShowPngPicture(d_width,d_height,d_parent);
         d_first_sync = true;
         set_title(d_title.c_str());

         d_linebuffer= new float[d_width];
         for(int i= 0; i < d_width; i++ )
          d_linebuffer[i]= 128;
         d_pixbuff = new unsigned char[d_width];
         d_linebuffer_pos=0;
         d_linecount=0;
         d_samples_since_last_sync = 0;
         d_sync_status = None;
         d_lost_syncs = 0;
         d_continuos_syncs = 0;
    }

    /*
     * Our virtual destructor.
     */
    show_syncedimage_impl::~show_syncedimage_impl() {
        delete d_linebuffer;
        delete d_pixbuff;
    }

    int
    show_syncedimage_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items) {

      std::stringstream sout;			  
			std::vector<gr::tag_t> synca;

      int samples_processed = 0 ;
      bool display = false;
      
      gr::thread::scoped_lock lock(d_setlock);
      const float *in = (const float *) input_items[0];
      // Find SyncA tag
      uint64_t nr = nitems_read(0);
      get_tags_in_range(synca, 0, nr, nr+noutput_items,pmt::mp("SyncA"));
      while ( samples_processed < noutput_items ) { // Process all samples
      switch ( d_sync_status ) {
      
          case None:
              if( synca.size() > 0 ) { // First sync detected
                 std::cout << "First sync at: " << synca[0].offset << std::endl;
                 samples_processed = synca[0].offset-nr;
                 d_samples_since_last_sync = 0;
                 synca.erase(synca.begin()); // Delete processed sync
                 d_sync_status = FirstSync;
                 d_continuos_syncs++;
              }
              else
                samples_processed = noutput_items;
              break;
              
          case FirstSync:
              if ( synca.size() > 0 ) { // Further sync detected
                if( accept_sync(d_samples_since_last_sync + (synca[0].offset-nr-samples_processed)) ) { // Sync accepted
                  std::cout << "Second Sync accepted, we are now in Sync: " << synca[0].offset << std::endl;
                  d_sync_status = InSync;
                }
                else { // Sync rejected
                  std::cout << "Second Sync rejected at: " << synca[0].offset << std::endl;
                }
                samples_processed = synca[0].offset-nr;
                synca.erase(synca.begin()); // Delete processed sync
                d_samples_since_last_sync = 0;
              }
             else { // No sync
                d_samples_since_last_sync += noutput_items-samples_processed;
                samples_processed = noutput_items;
             }
              break;
          case InSync: 
               if ( synca.size() > 0 ) { // Further sync detected
                if ( accept_sync(d_samples_since_last_sync + synca[0].offset-nr-samples_processed) ) { // Sync accepted
                    d_samples_since_last_sync = 0;
//                    std::cout << "Sync accepted at: " << synca[0].offset << std::endl;
                    int to_store = synca[0].offset-nr-samples_processed;
                    while( to_store-- > 0 ) {
                      d_linebuffer[d_linebuffer_pos++] = in[samples_processed++];
                      if ( d_linebuffer_pos >= d_width )
                        process_line(); // Write line
                    }
                    if (  d_linebuffer_pos > 0 ) {
                      if (  d_linebuffer_pos < tolerance ) {
                        std::cout << "****Ignore: " << d_linebuffer_pos << " pixels" << std::endl;
                        d_linebuffer_pos = 0;
                      }
                      else
                       process_line(); // Write possible incomplete line
                    }
                }
                else { // Rejected
//                     std::cout << "Sync rejected at: " << synca[0].offset << " Distance: " << (d_samples_since_last_sync + synca[0].offset-nr-samples_processed) << std::endl;
                }
                synca.erase(synca.begin()); // Delete processed sync              

               }
               else { // No sync
                int to_store = noutput_items - samples_processed;
                d_samples_since_last_sync += to_store;
                while( to_store-- > 0 ) {
                    d_linebuffer[d_linebuffer_pos++] = in[samples_processed++];
                    if ( d_linebuffer_pos >= d_width )
                        process_line(); // Write line
                    }
               }         
             break;
      
        }
      
      }
      return noutput_items;
    }

    void show_syncedimage_impl::displayBottomUp(bool direction)
    {
      d_main_gui->presetBottomUp(direction);
    }

    QWidget *
    show_syncedimage_impl::qwidget()
    {
      return d_main_gui;
    }
    PyObject *
    show_syncedimage_impl::pyqwidget()
    {

     PyObject *w = PyLong_FromVoidPtr((void*)d_main_gui);
     PyObject *retarg = Py_BuildValue("N", w);
     return retarg;
    }
    void show_syncedimage_impl::set_title(const char * title)
    {
      d_main_gui->setTitle(title);
    }
    void show_syncedimage_impl::process_line()
    {
      float scale;
      float f_min =  99999.;
      float f_max = -99999.;
      for(int i = 0; i < d_linebuffer_pos;i++) {
        f_min = fminf(f_min,d_linebuffer[i]);
        f_max = fmaxf(f_max,d_linebuffer[i]);
      }
      scale = 255/(f_max - f_min);     
      for(int i = 0; i < d_linebuffer_pos;i++)
        d_pixbuff[i] = (d_linebuffer[i] - f_min) * scale;
      if( d_linebuffer_pos < d_width ) { //Fill rest of buffer
        for(int i=d_linebuffer_pos;i < d_width;i++)
          d_pixbuff[i] = 65;
      } 
      if( d_linebuffer_pos < d_width )
        std::cout <<"+++++ " << d_linebuffer_pos <<" pixels written, filled up to: " << d_width << std::endl; 
      d_main_gui->setPixel(d_pixbuff,d_width);
      d_linebuffer_pos = 0;
    }

    
    bool show_syncedimage_impl::accept_sync(int count )
    {
      bool accept;
      accept = true;
      int linecount = count / d_width;
      if ( ( count % d_width ) > (d_width / 2 ) )
         linecount++; 
      if ( abs( count - linecount * d_width ) > (tolerance * linecount ) ) {
          accept = false;
          d_lost_syncs = linecount;
          if( d_continuos_syncs > 0 ) {
                std::cout <<"Continuos syncs: " << d_continuos_syncs << std::endl;
                d_continuos_syncs = 0;
          }      
      }
      else {
        d_continuos_syncs = linecount;
        if ( d_lost_syncs > 0) {
            std::cout <<"Lost syncs: " << d_lost_syncs << std::endl;
            d_lost_syncs = 0;
        }
      }
      
      return accept;
    }
  } /* namespace display */
} /* namespace gr */

