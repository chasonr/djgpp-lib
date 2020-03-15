# Top level makefile for djgpp-lib

default:
	$(MAKE) -C src

# Very complicated to figure out what builds what.
# Easier just to do a complete clean here.
clean:
	$(MAKE) -C src clean
	rm -rf bin etc hostbin share
	rm -f include/stubinfo.h
	rm -f lib/*.a
	rm -f info/*.info
	rm -rf zoneinfo/Africa/
	rm -rf zoneinfo/America/
	rm -rf zoneinfo/Antarctica/
	rm -rf zoneinfo/Arctic/
	rm -rf zoneinfo/Asia/
	rm -rf zoneinfo/Atlantic/
	rm -rf zoneinfo/Australia/
	rm -rf zoneinfo/Brazil/
	rm -rf zoneinfo/Canada/
	rm -rf zoneinfo/Chile/
	rm -rf zoneinfo/Etc/
	rm -rf zoneinfo/Europe/
	rm -rf zoneinfo/Indian/
	rm -rf zoneinfo/Mexico/
	rm -rf zoneinfo/Mideast/
	rm -rf zoneinfo/Pacific/
	rm -rf zoneinfo/US/
	rm -f zoneinfo/CET
	rm -f zoneinfo/CST6CDT
	rm -f zoneinfo/Cuba
	rm -f zoneinfo/EET
	rm -f zoneinfo/EST
	rm -f zoneinfo/EST5EDT
	rm -f zoneinfo/Egypt
	rm -f zoneinfo/Eire
	rm -f zoneinfo/Factory
	rm -f zoneinfo/GB
	rm -f zoneinfo/GB-Eire
	rm -f zoneinfo/GMT
	rm -f 'zoneinfo/GMT%0'
	rm -f zoneinfo/GMT-0
	rm -f zoneinfo/GMT0
	rm -f zoneinfo/Greenwich
	rm -f zoneinfo/HST
	rm -f zoneinfo/Hongkong
	rm -f zoneinfo/Iceland
	rm -f zoneinfo/Iran
	rm -f zoneinfo/Israel
	rm -f zoneinfo/Jamaica
	rm -f zoneinfo/Japan
	rm -f zoneinfo/Kwajalein
	rm -f zoneinfo/Libya
	rm -f zoneinfo/MET
	rm -f zoneinfo/MST
	rm -f zoneinfo/MST7MDT
	rm -f zoneinfo/NZ
	rm -f zoneinfo/NZ-CHAT
	rm -f zoneinfo/Navajo
	rm -f zoneinfo/PRC
	rm -f zoneinfo/PST8PDT
	rm -f zoneinfo/Poland
	rm -f zoneinfo/Portugal
	rm -f zoneinfo/ROC
	rm -f zoneinfo/ROK
	rm -f zoneinfo/Singapore
	rm -f zoneinfo/Turkey
	rm -f zoneinfo/UCT
	rm -f zoneinfo/UTC
	rm -f zoneinfo/Universal
	rm -f zoneinfo/W-SU
	rm -f zoneinfo/WET
	rm -f zoneinfo/Zulu
	rm -f zoneinfo/iso3166.tab
	rm -f zoneinfo/localtime
	rm -f zoneinfo/posixrules
	rm -f zoneinfo/zone.tab
