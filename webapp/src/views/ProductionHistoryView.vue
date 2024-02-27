<template>
    <BasePage :title="$t('menu.ProductionHistory')" :isLoading="dataLoading">
        <CardElement :text="$t('productionhistoryadmin.urlConfiguration')" textVariant="text-bg-primary">
          <InputElement :label="$t('productionhistoryadmin.fetchingUrl')" type="text" v-model="url"/>
        </CardElement>
        <FormFooter @reload="null"/>
    </BasePage>
</template>

<script lang="ts">
import { defineComponent } from 'vue';
import BasePage from '@/components/BasePage.vue';
import CardElement from '@/components/CardElement.vue';
import { authHeader, handleResponse } from '@/utils/authentication';
import FormFooter from '@/components/FormFooter.vue';
import InputElement from '@/components/InputElement.vue';

export default defineComponent({
    components: {
        BasePage,
        CardElement,
        FormFooter,
        InputElement,
    },
    data() {
        return {
            dataLoading: false,
            url: "",
        };
    },
    created() {
        this.getHistoryUrl();
    },
    methods: {
        getHistoryUrl() {
            // this.dataLoading = true;
            // fetch("/api/history-url", { headers: authHeader() })
            //     .then((response) => handleResponse(response, this.$emitter, this.$router))
            //     .then((data) => {
            //         this.ntpDataList = data;
            //         this.dataLoading = false;
            //     });
        },
    },
});
</script>