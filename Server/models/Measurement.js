const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const MeasureSchema = new Schema ({
  data: {
    type: Array
  },
  created: {
    type: Date
  },
  index: {
    type: Number
  }
})

module.exports = Measure = mongoose.model('measure', MeasureSchema);

