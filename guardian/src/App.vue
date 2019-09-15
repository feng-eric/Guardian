<template>
  <div id="app">
    <div>
      <b-jumbotron header="Guardian" style="width: 50%; margin: 0 auto; opacity: 0.9;" lead="Novel Approach to Firefighter Safety">
        <img style="opacity: 1" src="https://image.flaticon.com/icons/svg/206/206877.svg" height="200px"></img>
        <!-- <p>For more information visit website</p>
        <b-button variant="primary" href="#">More Info</b-button> -->
      </b-jumbotron>
    </div>
    <div class="mt-5">
      <div>
        <b-card-group deck>
          <b-card  v-bind:class="temperatureClassObject" header="Temperature" header-class="customFont" class="text-center">
    
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
                          <p class="card-text">Temperature displayed in Celsius degree.</p>
                      </div>
                    </div>
                    <div v-else>
                      <!-- <div @click=toggleTemperature>
                        Click to see current data
                      </div>   -->
                        <apexchart ref="temperatureChart" type=line :options="temperatureOptions" :series="tempSeries" />
                    </div>
              <b-alert class="bigText" show v-model="showTemperatureAlert" variant="danger">
                WARNING: Critical Temperature
              </b-alert>
          </b-card>

          <b-card v-bind:class="humidityClassObject" header="Humidity" header-class="customFont" class="text-center">
            <ToggleButton 
                      @change="toggleHumidity"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showHumidity">
                      <div class="card-body">
                          <h1 id="humidity" style="font-size: 75px;" class="card-title"><span> {{humidityData[humidityData.length - 1].y}}%</span></h1>
                          <p class="card-text">Relative humidity displayed in percentage.</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="humidityChart" type="line" :options="humidityOptions" :series="series"></apexchart>
                    </div>
              
          </b-card>
          <b-card v-bind:class="carbonDioxideClassObject" header="Carbon Dioxide" header-class="customFont" class="text-center">
              <ToggleButton 
                      @change="toggleCarbonDioxide"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showCarbonDioxide">
                      <div class="card-body">
                          <h1 id="carbonDioxide" style="font-size: 75px;" class="card-title"> {{carbonDioxideData[carbonDioxideData.length-1].y}}<span>ppb</span></h1>
                          <p class="card-text">Number articles of carbon of dioxide in the air in parts per billion.</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="carbonDioxideChart" type=line :options="carbonDioxideOptions" :series="carbonDioxideSeries" />
                    </div>
              <b-alert class="bigText" show v-model="showCarbonDioxideAlert" variant="danger">
                WARNING: Critical Carbon Dioxide Levels
              </b-alert>
          </b-card>
        </b-card-group>

      </div>
    </div>
    <div class="mt-5">
      <b-card-group deck>
        <b-card v-bind:class="totalVolatileOrganicCompoundClassObject" header="Total Volatile Organic Compound" header-class="customFont" class="text-center">
            <ToggleButton 
                      @change="toggleTotalVolatileOrganicCompound"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showTotalVolatileOrganicCompound">
                      <div class="card-body">
                          <h1 id="totalVolatileOrganicCompound" style="font-size: 75px;" class="card-title"> {{totalVolatileOrganicCompoundData[totalVolatileOrganicCompoundData.length-1].y}}<span>ppb</span></h1>
                          <p class="card-text">Total volatile organic compound in the air in parts per billion</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="totalVolatileOrganicChart" type=line :options="totalVolatileOrganicCompoundOptions" :series="totalVolatileOrganicCompoundSeries" />
                    </div>
                    <b-alert class="bigText" show v-model="showTotalVolatileOrganicCompoundAlert" variant="danger">
                WARNING: High Total Volatile Organic Compound Levels
                </b-alert>
        </b-card>

        <b-card bg-variant="light" header="Altitude" header-class="customFont" class="text-center">
            <ToggleButton 
                      @change="toggleAltitude"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showAltitude">
                      <div class="card-body">
                          <h1 id="altitude" style="font-size: 75px;" class="card-title"> {{altitudeData[altitudeData.length-1].y}}<span>metres</span></h1>
                          <p class="card-text">Altitude displayed in metres</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="altitudeChart" type=line :options="options" :series="altitudeSeries" />
                    </div>
        </b-card>

        <b-card bg-variant="light" header="Atomspheric Pressure" header-class="customFont" class="text-center">
          <ToggleButton 
                      @change="toggleAtmosphericPressure"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showAtmosphericPressure">
                      <div class="card-body">
                          <h1 id="atmosphericPressure" style="font-size: 75px;" class="card-title"> {{atomospherePressureData[atomospherePressureData.length-1].y}}<span>hPa</span></h1>
                          <p class="card-text">Atmospheric pressure displayed in metres</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="atmosphericPressureChart" type=line :options="options" :series="atmosphericPressureSeries" />
                    </div>
        </b-card>
      </b-card-group>
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
      humidity: 20,
      unsafeTemperature: true,
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
      toggleButtonWidth: 125,
      options: {
        chart: {
          id: 'vuechart-example'
        },
        colors: ['#0078FF']
      },
      dangerOptions: {
        chart: {
          id: 'vuechart-example'
        },
        xaxis: {  
          labels: {
            style: {
              fontSize: 16,
              color: '#FFFFFF'
            }
          }
        },
        yaxis: {
          labels: {
            style: {
               color: '#FFFFFF',
               fontSize: 16
            }
          }
        },
        colors: ['#FFFFFF']
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
  computed: {
    temperatureClassObject: function(){
      return {
        'bg-danger' : this.showTemperatureAlert,
        'bg-light': !this.showTemperatureAlert,
        'whiteText' : this.showTemperatureAlert,
      }
    },

    humidityClassObject: function(){
       return {
        'bg-danger' : this.showHumidityAlert,
        'bg-light': !this.showHumidityAlert,
        'whiteText' : this.showHumidityAlert,
      }
    },
    carbonDioxideClassObject: function(){
       return {
        'bg-danger' : this.showCarbonDioxideAlert,
        'bg-light': !this.showCarbonDioxideAlert,
        'whiteText' : this.showCarbonDioxideAlert,
      }
    },
    totalVolatileOrganicCompoundClassObject: function(){
       return {
        'bg-danger' : this.showTotalVolatileOrganicCompoundAlert,
        'bg-light': !this.showTotalVolatileOrganicCompoundAlert,
        'whiteText' : this.showTotalVolatileOrganicCompoundAlert,
      }
    },
    temperatureOptions: function(){ 
      return this.showTemperatureAlert ? this.dangerOptions : this.options
    },
    humidityOptions: function() {
      return this.showHumidityAlert ? this.dangerOptions : this.options
    },
    carbonDioxideOptions: function() {
      return this.showCarbonDioxideAlert ? this.dangerOptions : this.options
    },
    totalVolatileOrganicCompoundOptions: function() {
      return this.showTotalVolatileOrganicCompoundAlert ? this.dangerOptions : this.options
    }
  },
  watch: {
    
  },
  created() {
    const tempRef = database.ref('DHT11').child('temperature')
    const humRef = database.ref('DHT11').child('humidity')
    const coRef = database.ref('CCS811').child('CO2')
    const tvocRef = database.ref('CCS811').child('TVOC')
    const atomospherePressureRef = database.ref('BME280').child('Pressure')
    const altitudeRef = database.ref('BME280').child('Altitude')

    // tempRef.remove();
    // humRef.remove();
    // coRef.remove()
    // tvocRef.remove()
    // atomospherePressureRef.remove()
    // altitudeRef.remove()

    tempRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
    
      if (value >= 20) {
        this.showTemperatureAlert = true;
      } else {
        this.showTemperatureAlert = false;
      }
     
      this.temperatureData.push({ x : this.setTime(), y : value.toString()})
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
      
      this.humidityData.push({ x : this.setTime(), y : value.toString()})
      if (this.humidityData.length > 8) {
        this.humidityData = this.humidityData.slice(this.humidityData.length - 8, this.humidityData.length)
      }
      
      this.$refs.humidityChart.updateSeries([{
        data: this.humidityData
      }])

    });

    coRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)

      if (value.toString() > 1000) {
        this.showCarbonDioxideAlert = true;
      } else {
        this.showCarbonDioxideAlert = false;
      }

      this.carbonDioxideData.push({ x : this.setTime(), y : value.toString()})
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

      this.totalVolatileOrganicCompoundData.push({ x : this.setTime(), y : value.toString()})
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

      this.altitudeData.push({ x : this.setTime(), y : value.toString()})
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

      this.atomospherePressureData.push({ x : this.setTime(), y : value.toString()})
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
      this.showAtmosphericPressure = !this.showAtmosphericPressure
    },
    setTime() {
      var date = new Date()
      var hours = date.getHours()
      var minutes = date.getMinutes()
      var seconds = date.getSeconds()
      if (seconds < 10) {
        seconds = "0" + seconds.toString()
      }
      
      if (minutes < 10) {
        minutes = "0" + minutes.toString()
      }

      if (hours < 10) {
        hours = "0" +  hours.toString()
      }

      return hours + ":" + minutes + ":" + seconds
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
  .card {
    padding: 0 0 0 0;
    margin: 0 0 0 0;
  }

  .card-text {
    font-size: 23px;
  }
  .customFont {
    font-size: 40px;

  }
  .whiteText { 
    color: white;
  }
  .bigText {
    font-size: 25px;
  }
  
</style>
