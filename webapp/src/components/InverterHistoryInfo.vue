<template>
  <div>
    <InputElement @change="onDateChanged($event.target.value)" :max="getYesterdayDate()"
      :label="$t('inverterhistoryinfo.ChooseHistoryDay')" type="date" v-model="historyDate" />
  </div>
  <div class="row row-cols-1 row-cols-md-12 g-3">
    <div class="col">
      <CardElement centerContent textVariant="text-bg-success"
        :text="`${$t('inverterhistoryinfo.TotalYieldDay')} ${historyDate}`">
        <h2>
          {{ currentHistory?.yieldDay || $t('inverterhistoryinfo.NoData') }}
          <small class="text-muted" v-if="currentHistory?.yieldDay">Wh</small>
        </h2>
      </CardElement>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, type PropType } from 'vue';
import type { Total } from '@/types/LiveDataStatus';
import type { YieldHistory } from '@/types/YieldHistory';

import CardElement from './CardElement.vue';
import InputElement from './InputElement.vue';

export default defineComponent({
  components: {
    CardElement,
    InputElement,
  },
  data() {
    return {
      historyDate: {} as string,
      currentHistory: {} as YieldHistory | undefined,
    };
  },
  mounted() {
    this.historyDate = this.getYesterdayDate();
    this.onDateChanged(this.getYesterdayDate());
  },
  methods: {
    getYesterdayDate() {
      const currentDate = new Date();
      const year = currentDate.getFullYear();
      const month = String(currentDate.getMonth() + 1).padStart(2, '0');
      const day = String(currentDate.getDate() - 1).padStart(2, '0');
      return `${year}-${month}-${day}`;
    },
    onDateChanged(date: string) {
      this.historyDate = date;
      this.currentHistory = this.yieldHistories?.find((yi) => yi.date === date);
    }
  },
  props: {
    totalData: { type: Object as PropType<Total>, required: true },
    yieldHistories: { type: Object as PropType<YieldHistory[]>, required: false },
  },
});
</script>
