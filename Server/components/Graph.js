import React from 'react'
import { LineChart, XAxis, YAxis, Tooltip, CartesianGrid, Line, Legend } from 'recharts'

const rawData = [2937,1011,3710,2455,3509,4079,1878,3304,337,464,472,3974,2127,1860,638,1252,1072,1594,283,462,761,368,1801,973,3958,3098,2750,153,3516,2989,3307,3756,717,2041,1892,440,1557,3833,3155,178,2151,2989,975,2543,1453,2898,3474,188,2935,2157,1314,267,2578,3947,3606,4008,4041,1691,2539,870,1140,1506,3698,3714,3834,3905,1137,3131,2346,1292,3191,1176]

const data = rawData.map((d, i) => ({
  name: i,
  uv: d
}))



const Graph = () => (
  <LineChart width={1000} height={500} data={data}
    margin={{ top: 5, right: 30, left: 20, bottom: 5 }}>
    <CartesianGrid strokeDasharray="1500 1500" />
    <XAxis tick={false} />
    <YAxis />
    <Tooltip />
    <Line type="monotone" dataKey="uv" stroke="#82ca9d" />
  </LineChart>
)

export default Graph

