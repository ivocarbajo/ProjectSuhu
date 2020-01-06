var config = {
    title: "Temperature", //you can customize the title here
    refreshFrequency: 2, //refresh frequency in seconds
    recentHistoryUpdate: 10 //refresh recent history every n requests
}

document.getElementsByTagName("title")[0].innerHTML = config.title;

var requestCounter = 0;

var indicators = {
    celcius: document.getElementById("celciusIndicator"),
    fahrenheit: document.getElementById("fahrenheitIndicator"),
    humidity: document.getElementById("humidityIndicator")
}

function refreshData(){
    fetch("http://" + config.apiAddress).then(data => {
        return data.json();
    }).then(data => {
        indicators.celcius.innerText = data.celcius;
        indicators.fahrenheit.innerText = data.fahrenheit;
        indicators.humidity.innerText = data.humidity;

        if(requestCounter % config.recentHistoryUpdate == 0 || config.recentHistoryUpdate == 0){
            temperatureChart.data.labels.push("");
            humidityChart.data.labels.push("");
            temperatureChart.data.datasets[0].data.push(data.celcius);
            humidityChart.data.datasets[0].data.push(data.humidity);
            temperatureChart.update();
            humidityChart.update();
        }

        requestCounter++;
    }).catch(reason => {
        document.body.innerText = 
            "The API did not send a valid response or we werent able to send a query... Reason: " 
            + reason;
    });
}
refreshData();
setInterval(refreshData, config.refreshFrequency * 1000);