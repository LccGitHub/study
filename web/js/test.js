var GET = 'GET';
var POST = 'POST';


$(function () {



    var SWResultUrl = "../../cgi-bin/SWResult.py";
    var SWResultResult = "";
    //SWResultResult = curl(SWResultUrl, GET, 'SWResult');



});


function getCity(){
    var city = [
                ["Beijing", "Shanghai", "Shenzhen", "Washington", "Los Angeles", "Chicago","Cambridge", "London", "Scotland","Rome", "Milan", "Venice"],
                ["Beijing", "Shanghai", "Shenzhen"],
                ["Washington", "Los Angeles", "Chicago"],
                ["Cambridge", "London", "Scotland"],
                ["Rome", "Milan", "Venice"]
            ]
    var country_index = document.getElementById("select_country").selectedIndex; //get country index that selected
    var city_list = document.getElementById("select_city"); //get the object of city
    var city_array = city[country_index]; //get city array correspond selected country
    city_list.length =1; //Clear the city select box, leaving only tips options
    for (var i = 0; i < city_array.length; i++) {
        city_list[i + 1] = new Option(city_array[i], city_array[i]);
    }

}

