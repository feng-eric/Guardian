<template>
  <div id="app">
    <div>
      <b-jumbotron header="Guardian" style="width: 50%; margin: 0 auto; opacity: 0.9;" lead="Novel Approach to Firefighter Safety">
        <img style="opacity: 1" src="https://image.flaticon.com/icons/svg/206/206877.svg" height="200px"></img>
        <!-- <p>For more information visit website</p>
        <b-button variant="primary" href="#">More Info</b-button> -->
      </b-jumbotron>
    </div>
    <div class="row">
            <div class="col-sm-6"> <!-- Temperature Column -->
                <div class="card text-black bg-info mb-3" height=1000px style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Temperature</div>
                    <ToggleButton 
                      @change="toggleTemperature"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showTemperature">
                      <!-- <div @click=toggleTemperature>
                        Click to see chart
                      </div>   -->
                      <div class="card-body">
                          <h1 id="temperature" style="font-size: 75px;" class="card-title"> {{temperatureData[temperatureData.length-1].y}}°C</h1>
                          <p class="card-text">Temperature expressed in Celsius degree.</p>
                      </div>
                    </div>
                    <div v-else>
                      <!-- <div @click=toggleTemperature>
                        Click to see current data
                      </div>   -->
                        <apexchart ref="temperatureChart" type=line :options="options" :series="tempSeries" />
                    </div>
                </div>
                <b-alert show v-model="showTemperatureAlert" variant="danger">
                WARNING: Critical Temperature
                </b-alert>
            </div>
             
            <div class="col-sm-6"> <!-- Humidity Column -->
                <div class="card text-black bg-warning mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Humidity</div>
                     <ToggleButton 
                      @change="toggleHumidity"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showHumidity">
                      <div class="card-body">
                          <h1 id="humidity" style="font-size: 75px;" class="card-title"><span> {{humidityData[humidityData.length - 1].y}}%</span></h1>
                          <p class="card-text">Relative humidity, expressed in percentage.</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="humidityChart" type="line" :options="options" :series="series"></apexchart>
                    </div>
                </div>
                <b-alert show v-model="showHumidityAlert" variant="danger">
                WARNING: Critical Humidity
                </b-alert>
            </div>

            <div class="col-sm-6"> <!-- Carbon Dioxide Column -->
                <div class="card text-black bg-success mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Carbon Dioxide</div>
                     <ToggleButton 
                      @change="toggleCarbonDioxide"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showCarbonDioxide">
                      <div class="card-body">
                          <h1 id="carbonDioxide" style="font-size: 75px;" class="card-title"> {{carbonDioxideData[carbonDioxideData.length-1].y}}<span>ppm</span></h1>
                          <p class="card-text">DESCRIPTION</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="carbonDioxideChart" type=line :options="options" :series="carbonDioxideSeries" />
                    </div>
                </div>
                <b-alert show v-model="showCarbonDioxideAlert" variant="danger">
                WARNING: Critical Carbon Dioxide Levels
                </b-alert>
            </div>
             <div class="col-sm-6"> <!-- Total Volatile Column -->
                <div class="card text-black bg-light mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Total Volatile Organic Compound</div>
                     <ToggleButton 
                      @change="toggleTotalVolatileOrganicCompound"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showTotalVolatileOrganicCompound">
                      <div class="card-body">
                          <h1 id="totalVolatileOrganicCompound" style="font-size: 75px;" class="card-title"> {{totalVolatileOrganicCompoundData[totalVolatileOrganicCompoundData.length-1].y}}<span>ppm</span></h1>
                          <p class="card-text">DESCRIPTION</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="totalVolatileOrganicChart" type=line :options="options" :series="totalVolatileOrganicCompoundSeries" />
                    </div>
                </div>
                <b-alert show v-model="showTotalVolatileOrganicCompoundAlert" variant="danger">
                WARNING: High Total Volatile Organic Compound Levels
                </b-alert>
            </div>
            <div class="col-sm-6"> <!-- Total Altitude Column -->
                <div class="card text-black bg-light mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Altitude</div>
                     <ToggleButton 
                      @change="toggleAltitude"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showAltitude">
                      <div class="card-body">
                          <h1 id="altitude" style="font-size: 75px;" class="card-title"> {{altitudeData[altitudeData.length-1].y}}<span>metres</span></h1>
                          <p class="card-text">DESCRIPTION</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="altitudeChart" type=line :options="options" :series="altitudeSeries" />
                    </div>
                </div>
            </div>
            <div class="col-sm-6"> <!-- Total Atmospheric Pressure Column -->
                <div class="card text-black bg-light mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Atmospheric Pressure</div>
                     <ToggleButton 
                      @change="toggleAtmosphericPressure"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showAtmosphericPressure">
                      <div class="card-body">
                          <h1 id="atmosphericPressure" style="font-size: 75px;" class="card-title"> {{atomospherePressureData[atomospherePressureData.length-1].y}}<span>hPa</span></h1>
                          <p class="card-text">DESCRIPTION</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="atmosphericPressureChart" type=line :options="options" :series="atmosphericPressureSeries" />
                    </div>
                </div>
            </div>
    </div>
  </div>
</template>

<script>
import HelloWorld from './components/HelloWorld.vue'
import firebase from 'firebase'
import {database} from './main'

export default {
  name: 'app',
  components: {
    HelloWorld
  },
  data() {
    return {
      temperatureData: [],
      humidityData: [],
      carbonDioxideData: [],
      totalVolatileOrganicCompoundData: [],
      altitudeData: [],
      atomospherePressureData: [],
      showTemperature: true,
      showHumidity: true,
      showCarbonDioxide: true,
      showTotalVolatileOrganicCompound: true,
      showAltitude: true,
      showAtmosphericPressure: true,
      temperature: '',
      humidity: '',
      carbonDioxide: '',
      totalVolatileOrganicCompound: '',
      altitude: '',
      atmosphericpressure: '',
      toggleButtonWidth: 100,
      options: {
        chart: {
          id: 'vuechart-example'
        },
        xaxis: {
        },
        colors: ['#292121']
      },
      tempSeries: [{
        name: 'series-1',
        data: [0]
      }],
      carbonDioxideSeries: [{
        name: 'series-3',
        data: [0]
      }],
      totalVolatileOrganicCompoundSeries: [{
        name: 'series-4',
        data: [0]
      }],
      altitudeSeries: [{
        name: 'series-5',
        data: [0]
      }],
      atmosphericPressureSeries: [{
        name: 'series-5',
        data: [0]
      }],
      showTemperatureAlert: false,
      showHumidityAlert: false,
      showCarbonDioxideAlert: false,
      showTotalVolatileOrganicCompoundAlert: false
    }
  },

  created() {
    const tempRef = database.ref('DHT11').child('temperature')
    const humRef = database.ref('DHT11').child('humidity')
    const coRef = database.ref('CCS811').child('CO2')
    const tvocRef = database.ref('CCS811').child('TVOC')
    const atomospherePressureRef = database.ref('BME280').child('Altitude')
    const altitudeRef = database.ref('BME280').child('Pressure')

    // tempRef.remove();
    // humRef.remove();
    // coRef.remove()
    // tvocRef.remove()
    // atomospherePressureRef.remove()
    // altitudeRef.remove()

    tempRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
    
      if (value.toString() > 40) {
        this.showTemperatureAlert = true;
      } else {
        this.showTemperatureAlert = false;
      }
      var date = new Date()
      var hours = date.getHours()
      var minutes = date.getMinutes()
      var seconds = date.getSeconds()
      if (seconds < 10) {
        seconds = "0" + seconds.toString()
      }
      var time = hours + ":" + minutes + ":" + seconds
      this.temperatureData.push({ x : time, y : value.toString()})
      if (this.temperatureData.length > 8) {
        this.temperatureData = this.temperatureData.slice(this.temperatureData.length - 8, this.temperatureData.length)
      }
      this.$refs.temperatureChart.updateSeries([{
        data: this.temperatureData
      }])
    });

    humRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)

      if (value.toString() > 50) {
        this.showHumidityAlert = true;
      } else {
        this.showHumidityAlert = false;
      }
      
      var date = new Date()
      var hours = date.getHours()
      var minutes = date.getMinutes()
      var seconds = date.getSeconds()
      if (seconds < 10) {
        seconds = "0" + seconds.toString()
      }
      var time = hours + ":" + minutes + ":" + seconds
      this.humidityData.push({ x : time, y : value.toString()})
      if (this.humidityData.length > 8) {
        this.humidityData = this.humidityData.slice(this.humidityData.length - 8, this.humidityData.length)
      }
      this.$refs.humidityChart.updateSeries([{
        data: this.humidityData
      }])


      console.log("humidity: " + value);
     // this.humidity = value.toString();
    });

    coRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)

      if (value.toString() > 1000) {
        this.showCarbonDioxideAlert = true;
      } else {
        this.showCarbonDioxideAlert = true;
      }

      var date = new Date()
      var hours = date.getHours()
      var minutes = date.getMinutes()
      var seconds = date.getSeconds()
      if (seconds < 10) {
        seconds = "0" + seconds.toString()
      }
      var time = hours + ":" + minutes + ":" + seconds
      this.carbonDioxideData.push({ x : time, y : value.toString()})
      if (this.carbonDioxideData.length > 8) {
        this.carbonDioxideData = this.carbonDioxideData.slice(this.carbonDioxideData.length - 8, this.carbonDioxideData.length)
      }
      this.$refs.carbonDioxideChart.updateSeries([{
        data: this.carbonDioxideData
      }])
    });

    tvocRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)

      if (value.toString() > 200) {
        this.showTotalVolatileOrganicCompoundAlert = true;
      } else {
        this.showTotalVolatileOrganicCompoundAlert = false;
      }

      var date = new Date()
      var hours = date.getHours()
      var minutes = date.getMinutes()
      var seconds = date.getSeconds()
      if (seconds < 10) {
        seconds = "0" + seconds.toString()
      }
      var time = hours + ":" + minutes + ":" + seconds
      this.totalVolatileOrganicCompoundData.push({ x : time, y : value.toString()})
      if (this.totalVolatileOrganicCompoundData.length > 8) {
        this.totalVolatileOrganicCompoundData = this.totalVolatileOrganicCompoundData.slice(this.totalVolatileOrganicCompoundData.length - 8, this.totalVolatileOrganicCompoundData.length)
      }
      this.$refs.totalVolatileOrganicChart.updateSeries([{
        data: this.totalVolatileOrganicCompoundData
      }])
    });    

    altitudeRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)

      var date = new Date()
      var hours = date.getHours()
      var minutes = date.getMinutes()
      var seconds = date.getSeconds()
      if (seconds < 10) {
        seconds = "0" + seconds.toString()
      }
      var time = hours + ":" + minutes + ":" + seconds
      this.altitudeData.push({ x : time, y : value.toString()})
      if (this.altitudeData.length > 8) {
        this.altitudeData = this.altitudeData.slice(this.altitudeData.length - 8, this.altitudeData.length)
      }
      this.$refs.altitudeChart.updateSeries([{
        data: this.altitudeData
      }])
    }); 

    atomospherePressureRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)

      var date = new Date()
      var hours = date.getHours()
      var minutes = date.getMinutes()
      var seconds = date.getSeconds()
      if (seconds < 10) {
        seconds = "0" + seconds.toString()
      }
      var time = hours + ":" + minutes + ":" + seconds
      this.atomospherePressureData.push({ x : time, y : value.toString()})
      if (this.atomospherePressureData.length > 8) {
        this.atomospherePressureData = this.atomospherePressureData.slice(this.atomospherePressureData.length - 8, this.atomospherePressureData.length)
      }
      this.$refs.atmosphericPressureChart.updateSeries([{
        data: this.atomospherePressureData
      }])
    }); 

  },
  methods: {
    toggleTemperature(){
      console.log(this.showTemperature)
      this.showTemperature = !this.showTemperature;
    },
    toggleHumidity(){
      console.log(this.showHumidity)
      this.showHumidity = !this.showHumidity;
    },
    toggleCarbonDioxide(){
      console.log(this.showCarbonDioxide)
      this.showCarbonDioxide = !this.showCarbonDioxide;
    },
    toggleTotalVolatileOrganicCompound() {
      console.log(this.showTotalVolatileOrganicCompound)
      this.showTotalVolatileOrganicCompound = !this.showTotalVolatileOrganicCompound;
    },
    toggleAltitude() {
      console.log(this.showAltitude)
      this.showAltitude = !this.showAltitude
    },
    toggleAtmosphericPressure() {
      console.log(this.showAtmosphericPressure)
      this.showAtmosphericPressure = !this.showAltitude
    }
  }
};
</script>

<style>
body{
background-image: url("background2.jpg");
background-repeat: no-repeat;
height: 100%;
width: 100%;
background-size: cover;
}
#app {
  
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
 b-jumbotron {
  width: 50%;
  }

</style>
