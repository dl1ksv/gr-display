#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Display WxSat Image
# Author: DL1KSV
# Description: Receives and displays Noaa APT Images
# Generated: Wed Mar 27 12:19:37 2013
##################################################

execfile("/home/schroer/.grc_gnuradio/calcAmplitude.py")
execfile("/home/schroer/.grc_gnuradio/decodeApt.py")
execfile("/home/schroer/.grc_gnuradio/normalize.py")
from PyQt4 import Qt
from gnuradio import analog
from gnuradio import eng_notation
from gnuradio import fcd
from gnuradio import filter
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.gr import firdes
from gnuradio.qtgui import qtgui
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser
import PyQt4.Qwt5 as Qwt
import display
import sip
import sys

class DisplayPngExample(gr.top_block, Qt.QWidget):

	def __init__(self):
		gr.top_block.__init__(self, "Display WxSat Image")
		Qt.QWidget.__init__(self)
		self.setWindowTitle("Display WxSat Image")
		self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
		self.top_scroll_layout = Qt.QVBoxLayout()
		self.setLayout(self.top_scroll_layout)
		self.top_scroll = Qt.QScrollArea()
		self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
		self.top_scroll_layout.addWidget(self.top_scroll)
		self.top_scroll.setWidgetResizable(True)
		self.top_widget = Qt.QWidget()
		self.top_scroll.setWidget(self.top_widget)
		self.top_layout = Qt.QVBoxLayout(self.top_widget)
		self.top_grid_layout = Qt.QGridLayout()
		self.top_layout.addLayout(self.top_grid_layout)


		##################################################
		# Variables
		##################################################
		self.prefix = prefix = "/tmp/"
		self.sat = sat = 137620000
		self.samp_rate = samp_rate = 96000
		self.fileName = fileName = prefix+"Noaa15.wav"
		self.StartRecord = StartRecord = 1
		self.StartDisplay = StartDisplay = 1
		self.RxOffset = RxOffset = 1000
		self.MIXER = MIXER = 12
		self.LNA = LNA = 30

		##################################################
		# Blocks
		##################################################
		self.Rx = Qt.QTabWidget()
		self.Rx_widget_0 = Qt.QWidget()
		self.Rx_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.Rx_widget_0)
		self.Rx_grid_layout_0 = Qt.QGridLayout()
		self.Rx_layout_0.addLayout(self.Rx_grid_layout_0)
		self.Rx.addTab(self.Rx_widget_0, "Spectrum")
		self.Rx_widget_1 = Qt.QWidget()
		self.Rx_layout_1 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.Rx_widget_1)
		self.Rx_grid_layout_1 = Qt.QGridLayout()
		self.Rx_layout_1.addLayout(self.Rx_grid_layout_1)
		self.Rx.addTab(self.Rx_widget_1, "Image without pll")
		self.Rx_widget_2 = Qt.QWidget()
		self.Rx_layout_2 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.Rx_widget_2)
		self.Rx_grid_layout_2 = Qt.QGridLayout()
		self.Rx_layout_2.addLayout(self.Rx_grid_layout_2)
		self.Rx.addTab(self.Rx_widget_2, "Misc")
		self.top_layout.addWidget(self.Rx)
		self._sat_options = (137620000, 137500000, 137912500, 137100000, )
		self._sat_labels = ("Noaa15", "Noaa17", "Noaa18", "Noaa19", )
		self._sat_tool_bar = Qt.QToolBar(self)
		self._sat_tool_bar.addWidget(Qt.QLabel("sat"+": "))
		self._sat_combo_box = Qt.QComboBox()
		self._sat_tool_bar.addWidget(self._sat_combo_box)
		for label in self._sat_labels: self._sat_combo_box.addItem(label)
		self._sat_callback = lambda i: self._sat_combo_box.setCurrentIndex(self._sat_options.index(i))
		self._sat_callback(self.sat)
		self._sat_combo_box.currentIndexChanged.connect(
			lambda i: self.set_sat(self._sat_options[i]))
		self.Rx_grid_layout_0.addWidget(self._sat_tool_bar, 0,0,1,1)
		self._StartRecord_options = (1, 0, )
		self._StartRecord_labels = ("Stop", "Start", )
		self._StartRecord_group_box = Qt.QGroupBox("Start Recording")
		self._StartRecord_box = Qt.QVBoxLayout()
		self._StartRecord_button_group = Qt.QButtonGroup()
		self._StartRecord_group_box.setLayout(self._StartRecord_box)
		for i, label in enumerate(self._StartRecord_labels):
			radio_button = Qt.QRadioButton(label)
			self._StartRecord_box.addWidget(radio_button)
			self._StartRecord_button_group.addButton(radio_button, i)
		self._StartRecord_callback = lambda i: self._StartRecord_button_group.button(self._StartRecord_options.index(i)).setChecked(True)
		self._StartRecord_callback(self.StartRecord)
		self._StartRecord_button_group.buttonClicked[int].connect(
			lambda i: self.set_StartRecord(self._StartRecord_options[i]))
		self.top_layout.addWidget(self._StartRecord_group_box)
		self._LNA_layout = Qt.QVBoxLayout()
		self._LNA_tool_bar = Qt.QToolBar(self)
		self._LNA_layout.addWidget(self._LNA_tool_bar)
		self._LNA_tool_bar.addWidget(Qt.QLabel("LNA Gain"+": "))
		self._LNA_counter = Qwt.QwtCounter()
		self._LNA_counter.setRange(-5, 30, 2.5)
		self._LNA_counter.setNumButtons(2)
		self._LNA_counter.setValue(self.LNA)
		self._LNA_tool_bar.addWidget(self._LNA_counter)
		self._LNA_counter.valueChanged.connect(self.set_LNA)
		self._LNA_slider = Qwt.QwtSlider(None, Qt.Qt.Horizontal, Qwt.QwtSlider.BottomScale, Qwt.QwtSlider.BgSlot)
		self._LNA_slider.setRange(-5, 30, 2.5)
		self._LNA_slider.setValue(self.LNA)
		self._LNA_slider.setMinimumWidth(200)
		self._LNA_slider.valueChanged.connect(self.set_LNA)
		self._LNA_layout.addWidget(self._LNA_slider)
		self.Rx_grid_layout_0.addLayout(self._LNA_layout, 2,0,1,1)
		self.qtgui_sink_x_1 = qtgui.sink_c(
			1024, #fftsize
			firdes.WIN_BLACKMAN_hARRIS, #wintype
			sat-RxOffset, #fc
			samp_rate, #bw
			"Sat Spectrum", #name
			True, #plotfreq
			True, #plotwaterfall
			False, #plottime
			False, #plotconst
		)
		self.qtgui_sink_x_1.set_update_time(1.0 / 10)
		self._qtgui_sink_x_1_win = sip.wrapinstance(self.qtgui_sink_x_1.pyqwidget(), Qt.QWidget)
		self.Rx_grid_layout_0.addWidget(self._qtgui_sink_x_1_win, 4,0,2,3)
		self.normalize_0 = normalize()
		self.gr_wavfile_sink_0 = gr.wavfile_sink("/tmp/Noaa.wav", 2, samp_rate, 16)
		self.gr_threshold_ff_0_1 = gr.threshold_ff(-1, 0.9, 0)
		self.gr_threshold_ff_0 = gr.threshold_ff(25000, 30000, 0)
		self.gr_quadrature_demod_cf_0 = gr.quadrature_demod_cf(1)
		self.gr_multiply_xx_0 = gr.multiply_vcc(1)
		self.gr_float_to_uchar_0_0 = gr.float_to_uchar()
		self.gr_delay_0_0_0 = gr.delay(gr.sizeof_char*1, 38)
		self.gr_delay_0_0 = gr.delay(gr.sizeof_char*1, 38)
		self.gr_complex_to_float_0 = gr.complex_to_float(1)
		self.fir_filter_xxx_0_2_0 = filter.fir_filter_fff(1, ((-14,-14,-14,-14,-14,-14,-14,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,-14)))
		self.fcd_source_c_0 = fcd.source_c("FCD")
		self.fcd_source_c_0.set_lna_gain(LNA)
		self.fcd_source_c_0.set_freq(sat-RxOffset)
		    
		self.display_show_image_1 = display.show_image(
			2080,  # Picture width
			1400,  # Picture height
		)
		self._display_show_image_1_win = sip.wrapinstance(self.display_show_image_1.pyqwidget(), Qt.QWidget)
		self.Rx_layout_2.addWidget(self._display_show_image_1_win)
		self.display_show_image_0 = display.show_image(
			2080,  # Picture width
			1500,  # Picture height
		)
		self._display_show_image_0_win = sip.wrapinstance(self.display_show_image_0.pyqwidget(), Qt.QWidget)
		self.Rx_layout_1.addWidget(self._display_show_image_0_win)
		self.decodeApt_0 = decodeApt()
		self.calcAmplitude_0 = calcAmplitude()
		self.band_pass_filter_0 = gr.fir_filter_ccc(1, firdes.complex_band_pass(
			10, samp_rate, 100, 34000, 300, firdes.WIN_HAMMING, 6.76))
		self.analog_sig_source_x_0 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, -RxOffset, 1, 0)
		self.Start_1 = grc_blks2.valve(item_size=gr.sizeof_gr_complex*1, open=bool(StartRecord))
		self._StartDisplay_options = (1, 0, )
		self._StartDisplay_labels = ("Stop", "Start", )
		self._StartDisplay_group_box = Qt.QGroupBox("Start Displaing")
		self._StartDisplay_box = Qt.QVBoxLayout()
		self._StartDisplay_button_group = Qt.QButtonGroup()
		self._StartDisplay_group_box.setLayout(self._StartDisplay_box)
		for i, label in enumerate(self._StartDisplay_labels):
			radio_button = Qt.QRadioButton(label)
			self._StartDisplay_box.addWidget(radio_button)
			self._StartDisplay_button_group.addButton(radio_button, i)
		self._StartDisplay_callback = lambda i: self._StartDisplay_button_group.button(self._StartDisplay_options.index(i)).setChecked(True)
		self._StartDisplay_callback(self.StartDisplay)
		self._StartDisplay_button_group.buttonClicked[int].connect(
			lambda i: self.set_StartDisplay(self._StartDisplay_options[i]))
		self.Rx_grid_layout_0.addWidget(self._StartDisplay_group_box, 2,2,1,1)
		self._MIXER_layout = Qt.QVBoxLayout()
		self._MIXER_tool_bar = Qt.QToolBar(self)
		self._MIXER_layout.addWidget(self._MIXER_tool_bar)
		self._MIXER_tool_bar.addWidget(Qt.QLabel("Mixer Gain"+": "))
		self._MIXER_counter = Qwt.QwtCounter()
		self._MIXER_counter.setRange(4, 12, 1)
		self._MIXER_counter.setNumButtons(2)
		self._MIXER_counter.setValue(self.MIXER)
		self._MIXER_tool_bar.addWidget(self._MIXER_counter)
		self._MIXER_counter.valueChanged.connect(self.set_MIXER)
		self._MIXER_slider = Qwt.QwtSlider(None, Qt.Qt.Horizontal, Qwt.QwtSlider.BottomScale, Qwt.QwtSlider.BgSlot)
		self._MIXER_slider.setRange(4, 12, 1)
		self._MIXER_slider.setValue(self.MIXER)
		self._MIXER_slider.setMinimumWidth(200)
		self._MIXER_slider.valueChanged.connect(self.set_MIXER)
		self._MIXER_layout.addWidget(self._MIXER_slider)
		self.Rx_grid_layout_0.addLayout(self._MIXER_layout, 2,1,1,1)

		##################################################
		# Connections
		##################################################
		self.connect((self.fcd_source_c_0, 0), (self.gr_multiply_xx_0, 0))
		self.connect((self.analog_sig_source_x_0, 0), (self.gr_multiply_xx_0, 1))
		self.connect((self.fcd_source_c_0, 0), (self.qtgui_sink_x_1, 0))
		self.connect((self.Start_1, 0), (self.gr_complex_to_float_0, 0))
		self.connect((self.gr_complex_to_float_0, 0), (self.gr_wavfile_sink_0, 0))
		self.connect((self.gr_complex_to_float_0, 1), (self.gr_wavfile_sink_0, 1))
		self.connect((self.fcd_source_c_0, 0), (self.Start_1, 0))
		self.connect((self.gr_multiply_xx_0, 0), (self.decodeApt_0, 0))
		self.connect((self.fir_filter_xxx_0_2_0, 0), (self.gr_threshold_ff_0, 0))
		self.connect((self.gr_threshold_ff_0, 0), (self.gr_threshold_ff_0_1, 0))
		self.connect((self.gr_threshold_ff_0_1, 0), (self.gr_float_to_uchar_0_0, 0))
		self.connect((self.decodeApt_0, 2), (self.fir_filter_xxx_0_2_0, 0))
		self.connect((self.gr_float_to_uchar_0_0, 0), (self.display_show_image_0, 1))
		self.connect((self.decodeApt_0, 1), (self.gr_delay_0_0, 0))
		self.connect((self.gr_delay_0_0, 0), (self.display_show_image_0, 0))
		self.connect((self.gr_quadrature_demod_cf_0, 0), (self.calcAmplitude_0, 0))
		self.connect((self.gr_multiply_xx_0, 0), (self.band_pass_filter_0, 0))
		self.connect((self.band_pass_filter_0, 0), (self.normalize_0, 0))
		self.connect((self.normalize_0, 0), (self.gr_quadrature_demod_cf_0, 0))
		self.connect((self.calcAmplitude_0, 0), (self.gr_delay_0_0_0, 0))
		self.connect((self.gr_delay_0_0_0, 0), (self.display_show_image_1, 0))
		self.connect((self.calcAmplitude_0, 0), (self.display_show_image_1, 1))


	def get_prefix(self):
		return self.prefix

	def set_prefix(self, prefix):
		self.prefix = prefix
		self.set_fileName(self.prefix+"Noaa15.wav")

	def get_sat(self):
		return self.sat

	def set_sat(self, sat):
		self.sat = sat
		self.qtgui_sink_x_1.set_frequency_range(self.sat-self.RxOffset, self.samp_rate)
		self._sat_callback(self.sat)
		self.fcd_source_c_0.set_freq(self.sat-self.RxOffset)

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
		self.qtgui_sink_x_1.set_frequency_range(self.sat-self.RxOffset, self.samp_rate)
		self.band_pass_filter_0.set_taps(firdes.complex_band_pass(10, self.samp_rate, 100, 34000, 300, firdes.WIN_HAMMING, 6.76))

	def get_fileName(self):
		return self.fileName

	def set_fileName(self, fileName):
		self.fileName = fileName

	def get_StartRecord(self):
		return self.StartRecord

	def set_StartRecord(self, StartRecord):
		self.StartRecord = StartRecord
		self.Start_1.set_open(bool(self.StartRecord))
		self._StartRecord_callback(self.StartRecord)

	def get_StartDisplay(self):
		return self.StartDisplay

	def set_StartDisplay(self, StartDisplay):
		self.StartDisplay = StartDisplay
		self._StartDisplay_callback(self.StartDisplay)

	def get_RxOffset(self):
		return self.RxOffset

	def set_RxOffset(self, RxOffset):
		self.RxOffset = RxOffset
		self.analog_sig_source_x_0.set_frequency(-self.RxOffset)
		self.qtgui_sink_x_1.set_frequency_range(self.sat-self.RxOffset, self.samp_rate)
		self.fcd_source_c_0.set_freq(self.sat-self.RxOffset)

	def get_MIXER(self):
		return self.MIXER

	def set_MIXER(self, MIXER):
		self.MIXER = MIXER
		self._MIXER_counter.setValue(self.MIXER)
		self._MIXER_slider.setValue(self.MIXER)
		self.fcd_source_c_0.set_mixer_gain(self.MIXER)

	def get_LNA(self):
		return self.LNA

	def set_LNA(self, LNA):
		self.LNA = LNA
		self.fcd_source_c_0.set_lna_gain(self.LNA)
		self._LNA_counter.setValue(self.LNA)
		self._LNA_slider.setValue(self.LNA)

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	qapp = Qt.QApplication(sys.argv)
	tb = DisplayPngExample()
	tb.start()
	tb.show()
	qapp.exec_()
	tb.stop()

