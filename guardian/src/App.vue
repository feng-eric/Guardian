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
          <b-card :bg-variant="temperatureClassObject" header="Temperature" class="text-center">
    
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
                        <apexchart ref="temperatureChart" type=line :options="temperatureOptions" :series="tempSeries" />
                    </div>
              <b-alert show v-model="showTemperatureAlert" variant="danger">
                WARNING: Critical Temperature
              </b-alert>
          </b-card>

          <b-card :bg-variant="humidityClassObject" header="Humidity" class="text-center">
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
              
          </b-card>
          <b-card :bg-variant="carbonDioxideClassObject" header="Carbon Dioxide" class="text-center">
              <ToggleButton 
                      @change="toggleCarbonDioxide"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showCarbonDioxide">
                      <div class="card-body">
                          <h1 id="carbonDioxide" style="font-size: 75px;" class="card-title"> {{carbonDioxideData[carbonDioxideData.length-1].y}}<span>ppb</span></h1>
                          <p class="card-text">DESCRIPTION</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart ref="carbonDioxideChart" type=line :options="options" :series="carbonDioxideSeries" />
                    </div>
              <b-alert show v-model="showCarbonDioxideAlert" variant="danger">
                WARNING: Critical Carbon Dioxide Levels
              </b-alert>
          </b-card>
        </b-card-group>

      </div>
    </div>
    <div class="mt-5">
      <b-card-group deck>
        <b-card :bg-variant="TotalVolatileOrganicCompoundClassObject" header="Total Volatile Organic Compound" class="text-center">
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
                    <b-alert show v-model="showTotalVolatileOrganicCompoundAlert" variant="danger">
                WARNING: High Total Volatile Organic Compound Levels
                </b-alert>
        </b-card>

        <b-card bg-variant="light" header="Altitude" class="text-center">
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
        </b-card>

        <b-card bg-variant="light" header="Atomspheric Pressure" class="text-center">
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
      toggleButtonWidth: 100,
      options: {
        chart: {
          id: 'vuechart-example'
        },
        xaxis: {
        }
      },
      dangerOptions: {
        chart: {
          id: 'vuechart-example'
        },
        xaxis: {
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
      return this.showTemperatureAlert ? "danger" : "light"
    },
    humidityClassObject: function(){
      return this.showHumidityAlert ? "danger" : "light"
    },
    carbonDioxideClassObject: function(){
      return this.showCarbonDioxideAlert ? "danger" : "light"
    },
    totalVolatileOrganicCompoundClassObject: function(){
      return this.showTotalVolatileOrganicCompoundClassObject ? "danger" : "light"
    },
    temperatureOptions: function(){ 
      return this.showTemperatureAlert ? this.dangerOptions : this.options
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
     
      this.displayRecentData(this.temperatureData, value.toString())
      
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
      
      this.displayRecentData(this.humidityData, value.toString())
      
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

      this.displayRecentData(this.carbonDioxideData, value.toString())

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

      this.displayRecentData(this.totalVolatileOrganicCompoundData, value.toString())
      
      this.$refs.totalVolatileOrganicChart.updateSeries([{
        data: this.totalVolatileOrganicCompoundData
      }])
    });    

    altitudeRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)

      this.displayRecentData(this.altitudeData, value.toString())
      
      this.$refs.altitudeChart.updateSeries([{
        data: this.altitudeData
      }])
    }); 

    atomospherePressureRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)

      this.displayRecentData(this.atomospherePressureData, value.toString())

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
        hours = "0" +  minutes.toString()
      }

      return hours + ":" + minutes + ":" + seconds
    },
    displayRecentData(sensorData, dataPoint) {
      sensorData.push({ x : this.setTime(), y : dataPoint})
      if (sensorData.length > 8) {
        sensorData = sensorData.slice(sensorData.length - 8, sensorData.length)
      }
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
</style>
