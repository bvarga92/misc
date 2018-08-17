package main

import(
	"fmt"
	"net/http"
	"text/template"
	"time"
	"io/ioutil"
	"encoding/json"
	"os"
)

/* konstansok a lekerdezeshez (appid parancssori argumentum) */
var appid string
const cityID="7284824"

/* HTML template */
const htmlPage=`
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Current Weather</title>
</head>
<body>
	<ul>
		<li><b>City: </b>{{.City}}
		<li><b>GPS location: </b>{{.Coord.Lon}}, {{.Coord.Lat}}
		<li><b>Weather: </b>{{(index .Weather 0).Main}} ({{(index .Weather 0).Description}})
		<li><b>Temperature: </b>{{printf "%.2f" .Main.Temperature}} &#8451;
		<li><b>Humidity: </b>{{.Main.Humidity}} %
		<li><b>Pressure: </b>{{.Main.Pressure}} hPa
		<li><b>Wind: </b>{{.Wind.Speed}} m/s
		<li><b>Visibility: </b>{{.Visibility}} m
		<li><b>Sunrise: </b>{{.Sys.Sunrise}}
		<li><b>Sunset: </b>{{.Sys.Sunset}}
	</ul>
</body>
</html>
`

/* a JSON file szerkezetenek megfelelo strukturak */
type weatherdata_t struct{
	City        string      `json:"name"`
	Coord       coord_t     `json:"coord"`
	Weather     []weather_t `json:"weather"`
	Main        main_t      `json:"main"`
	Wind        wind_t      `json:"wind"`
	Visibility  float64     `json:"visibility"`
	Sys         sys_t       `json:"sys"`
}

type coord_t struct{
	Lon float64 `json:"lon"`
	Lat float64 `json:"lat"`
}

type weather_t struct{
	Main        string `json:"main"`
	Description string `json:"description"`
}

type main_t struct{
	Temperature float64 `json:"temp"`
	Pressure    float64 `json:"pressure"`
	Humidity    float64 `json:"humidity"`
}

type wind_t struct{
	Speed float64 `json:"speed"`
}

type sys_t struct{
	SunriseUnix int64 `json:"sunrise"`
	Sunrise     string
	SunsetUnix  int64 `json:"sunset"`
	Sunset      string
}

/* JSON file lekerese */
func GetJSON() string{
	response,err:=http.Get(fmt.Sprintf("https://api.openweathermap.org/data/2.5/weather?id=%s&appid=%s",cityID,appid))
	if err!=nil{
		panic(err)
	} else{
		defer response.Body.Close()
		contents,_:=ioutil.ReadAll(response.Body)
		return string(contents)
	}
}

/* JSON file feldolgozasa */
func ParseJSON(StrJSON string) *weatherdata_t{
	weatherdata:=new(weatherdata_t)
	json.Unmarshal([]byte(StrJSON),&weatherdata)
	weatherdata.Main.Temperature-=273.15
	weatherdata.Sys.Sunrise=fmt.Sprint(time.Unix(weatherdata.Sys.SunriseUnix,0))
	weatherdata.Sys.Sunset=fmt.Sprint(time.Unix(weatherdata.Sys.SunsetUnix,0))
	return weatherdata
}

/* HTTP keres kiszolgalasa */
func ServeHTTP(w http.ResponseWriter, req *http.Request){
	fmt.Println("Serving HTTP request at",time.Now())
	weatherdata:=ParseJSON(GetJSON())
	tmpl,_:=template.New("htmlTemplate").Parse(htmlPage)
	tmpl.Execute(w,weatherdata)
}

/* foprogram, inditja a szervert */
func main(){
	if len(os.Args)!=2{
		panic(fmt.Sprintf("Usage: %s [appid]",os.Args[0]))
	}
	appid=os.Args[1]
	fmt.Println("Starting HTTP server on port 80.")
	http.HandleFunc("/",ServeHTTP)
	http.ListenAndServe(":80",nil)
}
