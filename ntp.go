package main

import "fmt"
import "net"
import "encoding/binary"
import "time"
import "math"

type ntpPacket_t struct{
	LVM                 uint8
	Stratum             uint8
	PollInterval        int8
	Precision           int8
	RootDelay           int32
	RootDispersion      int32
	ReferenceID         uint32
	ReferenceTimestamp  uint64
	OriginateTimestamp  uint64
	ReceiveTimestamp    uint64
	TransmitTimestamp   uint64
}

func ntpFormatToTime(timestamp uint64) time.Time {
	elapsed := time.Duration(uint64(float64(timestamp)/4.294967296))
	return time.Date(1900,1,1,0,0,0,0,time.UTC).Add(elapsed)
}

func timeToNTPFormat(t time.Time) uint64 {
	ns  := uint64(t.Sub(time.Date(1900,1,1,0,0,0,0,time.UTC)))
	s_i := ns/1000000000
	s_f := ((ns-s_i*1000000000)<<32)/1000000000
	return (s_i<<32) | s_f
}

func printNTPData(p *ntpPacket_t){
	fmt.Println("")
	switch p.LVM>>6 {
		case 0: fmt.Println("Leap Indicator: No warning.")
		case 1: fmt.Println("Leap Indicator: Last minute has 61 seconds.")
		case 2: fmt.Println("Leap Indicator: Last minute has 59 seconds.")
		case 3: fmt.Println("Leap Indicator: Clock not synchronized.")
	}
	fmt.Println("Version:",(p.LVM>>3)&0x07)
	switch p.LVM&0x07 {
		case 0: fmt.Println("Mode: ???")
		case 1: fmt.Println("Mode: symmetric active")
		case 2: fmt.Println("Mode: symmetric passive")
		case 3: fmt.Println("Mode: client")
		case 4: fmt.Println("Mode: server")
		case 5: fmt.Println("Mode: broadcast")
		case 6: fmt.Println("Mode: NTP control message")
		case 7: fmt.Println("Mode: ???")
	}
	fmt.Println("Stratum level:",p.Stratum)
	fmt.Println("Poll interval:",math.Pow(2,float64(p.PollInterval)),"s")
	fmt.Printf("Precision: %e s\n",math.Pow(2,float64(p.Precision)))
	fmt.Printf("Root delay: %e s\n",float64(p.RootDelay)/65536)
	fmt.Printf("Root dispersion: %e s\n",float64(p.RootDispersion)/65536)
	fmt.Printf("Reference ID: 0x%X\n",p.ReferenceID)
	fmt.Println("Reference timestamp:",ntpFormatToTime(p.ReferenceTimestamp))
	fmt.Println("Originate timestamp:",ntpFormatToTime(p.OriginateTimestamp))
	fmt.Println("Receive timestamp:",ntpFormatToTime(p.ReceiveTimestamp))
	fmt.Println("Transmit timestamp:",ntpFormatToTime(p.TransmitTimestamp))
	fmt.Println("")
}

func main(){
	server := "0.hu.pool.ntp.org"
	addr, err := net.ResolveUDPAddr("udp",server+":123")
	if err != nil {
		fmt.Println("ERROR: unable to resolve address.")
		return
	}
	fmt.Println("")
	fmt.Println("Found",server,"at",addr)
	conn, err := net.DialUDP("udp",nil,addr)
	if err != nil {
		fmt.Println("ERROR: unable to connect.")
		return
	}
	defer conn.Close()
	conn.SetDeadline(time.Now().Add(10*time.Second))
	ntpPacket := new(ntpPacket_t)
	ntpPacket.LVM = 0x23; //no warning, v4, client
	ntpPacket.TransmitTimestamp = timeToNTPFormat(time.Now())
	err = binary.Write(conn,binary.BigEndian,ntpPacket)
	if err != nil {
		fmt.Println("ERROR: unable to send request.")
		return
	}
	err = binary.Read(conn,binary.BigEndian,ntpPacket)
	if err != nil {
		fmt.Println("ERROR: unable to get NTP packet.")
		return
	}
	printNTPData(ntpPacket)
}

