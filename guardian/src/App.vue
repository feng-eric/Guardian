<template>
  <div id="app">
    <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
    <!-- <HelloWorld msg="Welcome to Your Vue.js App"/> -->

    <div class="row">
       <b-alert show>Default Alert</b-alert>
            <div class="col-sm-6"> <!-- Temperature Column -->
                <div class="card text-white bg-warning mb-3" style="max-width: 18rem;">
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
                          <h1 id="temperature" style="font-size: 75px;" class="card-title"> {{temperature}}°C</h1>
                          <p class="card-text">Temperature expressed in Celsius degree.</p>
                      </div>
                    </div>
                    <div v-else>
                      <!-- <div @click=toggleTemperature>
                        Click to see current data
                      </div>   -->
                      <apexchart width="500" type="line" :options="options" :series="series"></apexchart>
                    </div>
                </div>
            </div>
            <div class="col-sm-6"> <!-- Humidity Column -->
                <div class="card text-white bg-primary mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Humidity</div>
                     <ToggleButton 
                      @change="toggleHumidity"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showHumidity">
                      <div class="card-body">
                          <h1 id="humidity" style="font-size: 75px;" class="card-title"> {{humidity}}<span>%</span></h1>
                          <p class="card-text">Relative humidity, expressed in percentage.</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart width="500" type="line" :options="options" :series="series"></apexchart>
                    </div>
                </div>
            </div>
            <div id="chart">
              <!--  -->
              <apexchart ref="realtimeChart" type=line height=350 :options="options" :series="series" />
            </div>
            <div>
              <b-alert>AHH</b-alert>
            </div>
    </div>
<b-table striped hover :items="items"></b-table>
  </div>
</template>

<script>
import HelloWorld from './components/HelloWorld.vue'
import firebase from 'firebase'
import {database} from './main'
// import ApexCharts from 'apexcharts'
// import VueApexCharts from 'vue-apexcharts'
// import Vue from 'vue'
// Vue.component('apexchart', VueApexCharts);
export default {
  name: 'app',
  components: {
    HelloWorld,
    // 'apexchart': ApexCharts
  },
  data() {
    return {
      temperatureData: [],
      showTemperature: true,
      showHumidity: true,
      temperature: '',
      humidity: '',
      toggleButtonWidth: 100,
      options: {
        chart: {
          id: 'vuechart-example'
        },
        xaxis: {
          categories: [1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998]
        }
      },
      series: [{
        name: 'series-1',
        data: [34, 53]
      }],
      items: [
          { age: 40, first_name: 'Dickerson', last_name: 'Macdonald' },
          { age: 21, first_name: 'Larsen', last_name: 'Shaw' },
          { age: 89, first_name: 'Geneva', last_name: 'Wilson' },
          { age: 38, first_name: 'Jami', last_name: 'Carney' }
        ]
 
    }
  },

  created() {
    const tempRef = database.ref('dht11').child('temperature')
    const humRef = database.ref('dht11').child('humidity')
    //tempRef.remove();
    //humRef.remove();

    tempRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
      console.log(value.toString())
      console.log("temp array before")
      console.log(this.temperatureData)
      console.log("temp array after")
      this.temperatureData.push(value.toString())
      console.log(this.temperatureData)
      // this.$refs.realtimeChart.updateSeries([{
      //   data: this.temperatureData
      // }])
      // getNewSeries(lastDate, {
      //   min: 20,
      //   max: 90
      // })
      // chart.updateSeries([{
      //   data: value
      // }])
      console.log("temperature: " + value);
      this.temperature = value.toString();
    });

    humRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
      
      console.log("humidity: " + value);
      this.humidity = value.toString();
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
    }
  }
};
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
