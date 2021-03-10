<template>
  <h1>eMalRob Remote Control</h1>
  <Keys />
  <Form />
</template>
<script>
import Keys from "./components/Keys";
import Form from "./components/Form";

export default {
  name: "App",
  components: {
    Keys,
    Form
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
