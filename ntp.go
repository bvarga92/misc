package main

import "fmt"
import "net"
import "net/http"
import "text/template"
import "encoding/binary"
import "time"
import "math"

/* NTP szerver cime */
const server = "0.hu.pool.ntp.org"

/* HTML template az egyszeru oldalhoz */
const simplePage = `
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>NTP Time</title>
</head>
<body>
	<p>{{.}}</p>
</body>
</html>
`

/* HTML template a reszletes infokhoz */
const detailedPage = `
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Detailed NTP Info</title>
</head>
<body>
	<ul>
		<li><b>Leap indicator: </b>{{.LeapIndicator}}
		<li><b>Version: </b>{{.Version}}
		<li><b>Mode: </b>{{.Mode}}
		<li><b>Stratum level: </b>{{.Stratum}}
		<li><b>Poll interval: </b>{{.PollInterval}}
		<li><b>Precision: </b>{{.Precision}}
		<li><b>Root delay: </b>{{.RootDelay}}
		<li><b>Root dispersion: </b>{{.RootDispersion}}
		<li><b>Reference ID: </b>{{.ReferenceID}}
		<li><b>Reference timestamp: </b>{{.ReferenceTimestamp}}
		<li><b>Originate timestamp: </b>{{.OriginateTimestamp}}
		<li><b>Receive timestamp: </b>{{.ReceiveTimestamp}}
		<li><b>Transmit timestamp: </b>{{.TransmitTimestamp}}
	</ul>
</body>
</html>
`

/* NTP uzenettipus */
type ntp_t struct{
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

/* ugyanez szovegesen (a template kitoltesehez) */
type context_t struct{
	LeapIndicator       string
	Version             string
        Mode                string
	Stratum             string
	PollInterval        string
	Precision           string
	RootDelay           string
	RootDispersion      string
	ReferenceID         string
	ReferenceTimestamp  string
	OriginateTimestamp  string
	ReceiveTimestamp    string
	TransmitTimestamp   string
}

/* konverzio 32.32 fixpontos formatumbol idoformatumba */
func NTPFormatToTime(timestamp uint64) time.Time {
	elapsed := time.Duration(uint64(float64(timestamp)/4.294967296))
	return time.Date(1900,1,1,0,0,0,0,time.UTC).Add(elapsed)
}

/* konverzio idoformatumbol 32.32 fixpontos formatumba */
func TimeToNTPFormat(t time.Time) uint64 {
	ns  := uint64(t.Sub(time.Date(1900,1,1,0,0,0,0,time.UTC)))
	s_i := ns/1000000000
	s_f := ((ns-s_i*1000000000)<<32)/1000000000
	return (s_i<<32) | s_f
}

/* vegrehajt egy NTP lekerdezest */
func NTPRequest() *ntp_t {
	ntpPacket := new(ntp_t)
	addr, err := net.ResolveUDPAddr("udp",server+":123")
	if err != nil {
		fmt.Println("ERROR: unable to resolve address.")
		return nil
	}
	fmt.Println("    Found",server,"at",addr)
	conn, err := net.DialUDP("udp",nil,addr)
	if err != nil {
		fmt.Println("ERROR: unable to connect.")
		return nil
	}
	defer conn.Close()
	conn.SetDeadline(time.Now().Add(10*time.Second))
	ntpPacket.LVM = 0x23 //no warning, v4, client
	ntpPacket.TransmitTimestamp = TimeToNTPFormat(time.Now())
	err = binary.Write(conn,binary.BigEndian,ntpPacket)
	if err != nil {
		fmt.Println("ERROR: unable to send request.")
		return nil
	}
	err = binary.Read(conn,binary.BigEndian,ntpPacket)
	if err != nil {
		fmt.Println("ERROR: unable to get NTP packet.")
		return nil
	}
	return ntpPacket
}

/* http://localhost:8080/ kiszolgalo */
func ServeHTTP(w http.ResponseWriter, req *http.Request){
	fmt.Println("Serving HTTP request at",time.Now())
	ntpPacket := NTPRequest()
	if ntpPacket != nil {
		tmpl,err := template.New("htmlTemplate").Parse(simplePage)
		if err == nil {
			tmpl.Execute(w,NTPFormatToTime(ntpPacket.TransmitTimestamp))
		}
	}
}

/* http://localhost:8080/details kiszolgalo */
func ServeHTTPDetails(w http.ResponseWriter, req *http.Request){
	fmt.Println("Serving HTTP request at",time.Now())
	ntpPacket := NTPRequest()
	if ntpPacket != nil {
		tmpl,err := template.New("htmlTemplate").Parse(detailedPage)
		if err == nil {
			context := new(context_t)
			switch ntpPacket.LVM>>6 {
				case 0: context.LeapIndicator=fmt.Sprint("No warning.")
				case 1: context.LeapIndicator=fmt.Sprint("Last minute has 61 seconds.")
				case 2: context.LeapIndicator=fmt.Sprint("Last minute has 59 seconds.")
				case 3: context.LeapIndicator=fmt.Sprint("Clock not synchronized.")
			}
			context.Version=fmt.Sprint((ntpPacket.LVM>>3)&0x07)
			switch ntpPacket.LVM&0x07 {
				case 0: context.Mode=fmt.Sprint("???")
				case 1: context.Mode=fmt.Sprint("symmetric active")
				case 2: context.Mode=fmt.Sprint("symmetric passive")
				case 3: context.Mode=fmt.Sprint("client")
				case 4: context.Mode=fmt.Sprint("server")
				case 5: context.Mode=fmt.Sprint("broadcast")
				case 6: context.Mode=fmt.Sprint("NTP control message")
				case 7: context.Mode=fmt.Sprint("???")
			}
			context.Stratum=fmt.Sprint(ntpPacket.Stratum)
			context.PollInterval=fmt.Sprint(math.Pow(2,float64(ntpPacket.PollInterval)),"s")
			context.Precision=fmt.Sprintf("%e s",math.Pow(2,float64(ntpPacket.Precision)))
			context.RootDelay=fmt.Sprintf("%e s",float64(ntpPacket.RootDelay)/65536)
			context.RootDispersion=fmt.Sprintf("%e s",float64(ntpPacket.RootDispersion)/65536)
			context.ReferenceID=fmt.Sprintf("0x%X",ntpPacket.ReferenceID)
			context.ReferenceTimestamp=fmt.Sprint(NTPFormatToTime(ntpPacket.ReferenceTimestamp))
			context.OriginateTimestamp=fmt.Sprint(NTPFormatToTime(ntpPacket.OriginateTimestamp))
			context.ReceiveTimestamp=fmt.Sprint(NTPFormatToTime(ntpPacket.ReceiveTimestamp))
			context.TransmitTimestamp=fmt.Sprint(NTPFormatToTime(ntpPacket.TransmitTimestamp))
			tmpl.Execute(w,context)
		}
	}
}

/* HTTP szerver inditasa */
func main(){
	mux := http.NewServeMux()
	mux.HandleFunc("/",ServeHTTP)
	mux.HandleFunc("/details",ServeHTTPDetails)
	fmt.Println("Starting HTTP server on port 8080.")
	http.ListenAndServe(":8080",mux)
}

