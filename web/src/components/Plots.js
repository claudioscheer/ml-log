import React, { useEffect, useState } from 'react';
import Plot from 'react-plotly.js';
import { Grid } from '@material-ui/core';
import applicationRedisSingleton from '../services/ApplicationRedisSingleton';
import eventEmitter from '../services/EventEmitter';
import config from '../config.json';

async function getKeys() {
    let promise = fetch(
        `${config.endpoint}/api/query/keys?` +
            new URLSearchParams({
                applicationName: applicationRedisSingleton.applicationName,
                redisHost: applicationRedisSingleton.redisHost,
                redisPort: applicationRedisSingleton.redisPort,
                redisDatabaseIndex:
                    applicationRedisSingleton.redisDatabaseIndex,
            }),
    );

    console.log(config);
}

function PlotsRoute() {
    const [plots, setPlots] = useState([]);

    eventEmitter.on('add-plot', (data) => {
        setPlots([...plots, data]);
    });

    useEffect(() => {
        getKeys();
    }, []);

    return (
        <div>
            <Grid container spacing={3}>
                {plots.map((x, i) => {
                    return (
                        <Grid item md={12} lg={6} key={i}>
                            <Plot
                                data={[
                                    {
                                        x: [1, 2, 3],
                                        y: [2, 6, 3],
                                        type: 'scatter',
                                        mode: 'lines+markers',
                                    },
                                    {
                                        x: [1, 2, 3] * 2,
                                        y: [2, 6, 3],
                                        type: 'scatter',
                                        mode: 'lines+markers',
                                    },
                                ]}
                                layout={{ title: x.title }}
                            />
                        </Grid>
                    );
                })}
            </Grid>
        </div>
    );
}

export default PlotsRoute;
