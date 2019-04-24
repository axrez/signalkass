const express = require('express');

const router = express.Router();

const Measure = require('../../models/Measurement');
const MeasureMap = require('../../models/MeasurementMap');

router.get('/', (req, res) => {
  Measure.find()
    .limit(1)
    .sort({ $natural: -1 })
    .then(m => res.json(m))
    .catch(err => console.log(err));
});

router.get('/map', (req, res) => {
  MeasureMap.find()
    .limit(10)
    .sort({ $natural: -1 })
    .then(m => res.json(m))
    .catch(err => console.log(err));
});

module.exports = router;
