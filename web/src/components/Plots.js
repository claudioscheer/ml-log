import React, { useEffect, useState } from 'react';
import Plot from 'react-plotly.js';
import { Grid } from '@material-ui/core';
import applicationRedisSingleton from '../services/ApplicationRedisSingleton';
import eventEmitter from '../services/EventEmitter';
import config from '../config.json';

async function getAllPlots() {
    try {
        let request = await fetch(
            `${config.endpoint}/api/query/xy-items?` +
                new URLSearchParams({
                    applicationName: applicationRedisSingleton.applicationName,
                    redisHost: applicationRedisSingleton.redisHost,
                    redisPort: applicationRedisSingleton.redisPort,
                    redisDatabaseIndex:
                        applicationRedisSingleton.redisDatabaseIndex,
                }),
        );

        const data = await request.json();
        return data;
    } catch (e) {
        return [];
    }
}

function PlotsRoute() {
    const [plots, setPlots] = useState([]);

    useEffect(() => {
        const refreshPlots = async () => {
            const allPlots = await getAllPlots();
            setPlots(allPlots);
        };
        refreshPlots();
        eventEmitter.on('refresh-plots', () => {
            refreshPlots();
        });
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
                                        x: x.items.map((z) => z.x),
                                        y: x.items.map((z) => z.y),
                                        type: 'scatter',
                                        mode: 'lines+markers',
                                    },
                                ]}
                                layout={{ title: x.key }}
                            />
                        </Grid>
                    );
                })}
            </Grid>
        </div>
    );
}

export default PlotsRoute;
