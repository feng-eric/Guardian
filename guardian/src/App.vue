<template>
  <div id="app">
    <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
    <!-- <HelloWorld msg="Welcome to Your Vue.js App"/> -->

    <div class="row">
            <div class="col-sm-6"> <!-- Temperature Column -->
                <div class="card text-white bg-warning mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Temperature</div>
                    <div class="card-body">
                        <h1 id="temperature" style="font-size: 75px;" class="card-title"> {{temperature}}°C</h1>
                        <p class="card-text">Temperature expressed in Celsius degree.</p>
                    </div>
                </div>
            </div>
            <div class="col-sm-6"> <!-- Humidity Column -->
                <div class="card text-white bg-primary mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Humidity</div>
                    <div class="card-body">
                        <h1 id="humidity" style="font-size: 75px;" class="card-title"> {{humidity}}<span>%</span></h1>
                        <p class="card-text">Relative humidity, expressed in percentage.</p>
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
      temperature: '',
      humidity: ''
    }
  },

  created() {
    const tempRef = database.ref('dht11').child('temperature')
    const humRef = database.ref('dht11').child('humidity')
    tempRef.remove();
    humRef.remove();

    tempRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
      
      console.log("temperature: " + value);
      this.temperature = value.toString();
    });

    humRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
      
      console.log("humidity: " + value);
      this.humidity = value.toString();
    });

    

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
