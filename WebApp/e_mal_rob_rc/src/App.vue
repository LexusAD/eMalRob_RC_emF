<template>
  <h1>eMalRob Remote Control</h1>
  <Inputs />
  <div class="container">
    <div class="row">
      <form class="col s12 m8 l8 xl8">
        <div class="row">
          <div class="input-field col s12 m9 l6 xl6 offset-xl5 offset-l5 offset-m2">
            <i class="material-icons prefix">settings_ethernet</i>
            <input id="icon_prefix" type="text" />
            <label for="icon_prefix">Websocket Adress</label>
          </div>
          <div class="input-field col s1 m1 l1 xl1">
            <a class="waves-effect waves-light btn inline blue darken-1">Connect</a>
          </div>
        </div>
      </form>
    </div>
  </div>
</template>
<script>
import Inputs from "./components/Inputs";

export default {
  name: "App",
  components: {
    Inputs
  }
};
</script>

<style lang="scss">
$primary-color: color("materialize-red", "lighten-2") !default;
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
.active {
  color: #000 !important;
}
input[type="text"]:focus {
  border-bottom: 1px solid #000 !important;
  box-shadow: 0 1px 0 0 #000 !important;
}
</style>
